from models.nerf_model import NeRF
from train.loss import mse_loss
import torch
from tqdm import tqdm
from utils.positional_encoding import positional_encoding, volume_rendering
# from utils.render_image import get_rays, render_image
import torch.nn as nn
import torch.nn.functional as F
import numpy as np
import cv2
from utils import utils_blender # import load_blender, get_rays
from utils import utils_mvmp # import load_mvmp, get_rays

N_epochs = 5
N_iters = 200000 # 200000

def train(datadir="./data/nerf_synthetic/lego"):
    # images : [batch, height, width, 3] => RGB 이미지들
    # poses : [batch, 4, 4] => camera-to-world 변환 행렬
    # render_poses : [batch, 4, 4] => camera path
    # hwf : [height, width, focal] => h, w, f
    # i_split : [train, val, test]
    if datadir == "./data/nerf_synthetic/lego":
        near = 0.0
        far = 4.0
        images, poses, render_poses, hwf, i_split = utils_blender.load_data(datadir, half_res=True)
    elif datadir == "./data/converted_panoptic":
        near = 0.0
        far = 4.0
        images, poses, render_poses, hwf, i_split = utils_mvmp.load_data(datadir, half_res=True)
    else:
        raise ValueError("Unsupported dataset type")

    i_train, i_val, i_test = i_split
    print("train idx:", i_train)
    H_full, W_full, focal_full = map(int, hwf)

    center = poses[:, :3, 3].mean(0)
    camera_pos = poses[i_train[0], :3, 3]
    dist = np.linalg.norm(center - camera_pos)
    print("Scene-Camera dist:", dist)

    # 2. 모든 학습 이미지로부터 ray와 RGB 추출
    all_rays_o, all_rays_d, all_target_rgb = [], [], []

    for idx in i_train:
        img = torch.from_numpy(images[idx])
        # print("RGB image min/max:", img.min().item(), img.max().item())

        pose = torch.from_numpy(poses[idx])
        H, W = img.shape[:2]

        # print("H:", H, "W:", W)
        # print("H_full:", H_full, "W_full:", W_full)
        if datadir == "./data/nerf_synthetic/lego":
            rays_o, rays_d = utils_blender.get_rays(H, W, focal_full, pose)
        elif datadir == "./data/converted_panoptic":
            rays_o, rays_d = utils_mvmp.get_rays(H, W, focal_full, pose)
        else:
            raise ValueError("Unsupported dataset type")

        all_rays_o.append(rays_o)
        all_rays_d.append(rays_d)
        rgb = img[..., :3]          # RGBA → RGB만 슬라이싱
        rgb_flat = rgb.reshape(-1, 3)
        all_target_rgb.append(rgb_flat.reshape(-1, 3))

    # 3. 하나의 큰 텐서로 합치기
    rays_o = torch.cat(all_rays_o, dim=0)
    rays_d = torch.cat(all_rays_d, dim=0)
    target_rgb = torch.cat(all_target_rgb, dim=0)

    print(f"Total rays: {rays_o.shape[0]}")

    # 4. 모델 생성 및 학습
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    print("Using device:", device)

    model = NeRF(L_pos=10, L_dir=4, hidden_dim=256).to(device)
    rays_o = rays_o.to(device)
    rays_d = rays_d.to(device)
    target_rgb = target_rgb.to(device)
    optimizer = torch.optim.Adam(model.parameters(), lr=5e-4)

    N_samples = 128
    train_model(model, rays_o, rays_d, target_rgb, near, far, optimizer, mse_loss, N_samples=N_samples, epochs=N_epochs)

    if datadir == "./data/nerf_synthetic/lego":
        rgb_img = utils_blender.render_image(model, torch.from_numpy(poses[i_train[0]]), H_full, W_full, focal_full, device)
    elif datadir == "./data/converted_panoptic":
        rgb_img = utils_mvmp.render_image(model, torch.from_numpy(poses[i_train[0]]), H_full, W_full, focal_full, device)
    else:
        raise ValueError("Unsupported dataset type")

    cv2.imwrite("rendered_train_pose.png", rgb_img)
    original = (images[idx] * 255).astype(np.uint8)
    cv2.imwrite("original_reference.png", original)

    torch.save(model.state_dict(), "logs/nerf_mvmp.pt")
    print("✅ 모델 저장 완료!")

def train_model(model, rays_o, rays_d, target_rgb, near, far, optimizer, loss_fn, N_samples, epochs=5, batch_size=1024):
    model.train()
    device = rays_o.device  # 자동 감지

    N_rays = rays_o.shape[0]
    decay_rate = 0.1
    decay_steps = 30000  # 학습률을 줄이는 간격 (iteration 기준)

    best_loss = float('inf')
    patience = 5
    patience_counter = 0

    for epoch in range(epochs):
        perm = torch.randperm(N_rays, device=device)
        rays_o = rays_o[perm]
        rays_d = rays_d[perm]
        target_rgb = target_rgb[perm]

        rays_o = rays_o.to(device).float()
        rays_d = rays_d.to(device).float()
        target_rgb = target_rgb.to(device).float()

        total_loss = 0.0
        # iteration 수 정의
        N_rand = 1024  # iteration당 샘플 수
        N_rays = rays_o.shape[0]
        global_step = 0
        print("Start training with iteration-based batching!")

        for i in range(N_iters):
            new_lrate = 5e-4 * (decay_rate ** (global_step / decay_steps))
            for param_group in optimizer.param_groups:
                param_group['lr'] = new_lrate

            # 매 iteration마다 N_rand 개의 ray를 랜덤하게 선택
            select_inds = torch.randint(0, N_rays, (N_rand,), device=device)
            ro = rays_o[select_inds].to(device).float()
            rd = rays_d[select_inds].to(device).float()
            rgb_gt = target_rgb[select_inds].to(device).float()

            # 샘플링
            z_vals = torch.linspace(near, far, N_samples, device=device).expand(ro.shape[0], N_samples)
            points = ro[..., None, :] + rd[..., None, :] * z_vals[..., :, None]
            view_dir = F.normalize(rd, dim=-1)  # [B, 3]
            view_enc = positional_encoding(view_dir, L=4)

            # Repeat view direction for each sample point
            view_enc_repeated = view_enc[:, None, :].expand(-1, N_samples, -1).reshape(-1, view_enc.shape[-1])

            points_flat = points.reshape(-1, 3)
            pos_enc = positional_encoding(points_flat, L=10)

            raw = model(pos_enc, view_enc_repeated).view(ro.shape[0], N_samples, 4)
            sigma = F.softplus(raw[..., 3])
            raw = torch.cat([raw[..., :3], sigma.unsqueeze(-1)], dim=-1)

            rgb_pred = volume_rendering(raw, z_vals)
            loss = loss_fn(rgb_pred, rgb_gt)

            if torch.isnan(loss) or torch.isinf(loss):
                print(f"⚠️ Skipping iteration {i} with invalid loss = {loss}")
                continue

            optimizer.zero_grad()
            loss.backward()
            optimizer.step()
            global_step += 1
            if i % 1000 == 0:
                print(f"[Iter {i}] Loss: {loss.item():.6f}")

            total_loss += loss.item()


        avg_loss = total_loss / N_iters
        print(f"Epoch {epoch+1}, Avg Loss: {avg_loss:.6f}")

        # Early stopping 조건 확인
        if avg_loss < best_loss:
            best_loss = avg_loss
            patience_counter = 0
            # ✅ 모델 저장
            torch.save(model.state_dict(), "best_model.pth")
            print(f"📦 Saved new best model at epoch {epoch+1}")
        else:
            patience_counter += 1
            print(f"⚠️ Loss did not improve. Patience: {patience_counter}/{patience}")

            if patience_counter >= patience:
                print("🛑 Early stopping triggered.")
                break