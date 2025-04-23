import torch
import os
import cv2
import json
import numpy as np
from pathlib import Path

from torch.utils.data import DataLoader, TensorDataset
from models.nerf_model import NeRF
from train.trainer import train_model
from train.loss import mse_loss
from utils.positional_encoding import positional_encoding, volume_rendering
from load_mvmp import load_mvmp_data
import torch.nn as nn
import torch.nn.functional as F

basedir = "./logs"
expname = "mvmp_panoptic"
# datadir = "./data/converted_panoptic"
datadir = "./data/nerf_synthetic/lego"
dataset_type = "blender"


def load_data(frame_num = 0):
    data_path = './data/panoptic'
    seq_name = '171204_pose1_sample'
    import cv2
    # Load camera calibration parameters (for visualizing cameras)
    with open(data_path+'/calibration_{0}.json'.format(seq_name)) as cfile:
        calib = json.load(cfile)

    # Cameras are identified by a tuple of (panel#,node#)
    cameras = {(cam['panel'],cam['node']):cam for cam in calib['cameras']}

    # Convert data into numpy arrays for convenience
    for k,cam in cameras.items():
        cam['K'] = np.matrix(cam['K'])
        cam['distCoef'] = np.array(cam['distCoef'])
        cam['R'] = np.matrix(cam['R'])
        cam['t'] = np.array(cam['t']).reshape((3,1))
        #R = cv2.Rodrigues(cam['R'])[0]
        RT = np.hstack((cam['R'], cam['t']))
        cam['P'] = cam['K'] @ RT

    # Choose only HD cameras for visualization
    hd_cam_idx = zip([0] * 30,range(0,30))
    hd_cameras = [cameras[cam].copy() for cam in hd_cam_idx]

    import cv2
    import matplotlib.pyplot as plt

    img_path = data_path + "/hdImgs/"

    images = {}
    #cams = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    cams = range(0, 30)

    for cam_id in cams:
        img_file = img_path + "00_{}/".format(str(cam_id).zfill(2)) + "00_{}_{}.jpg".format(str(cam_id).zfill(2), str(frame_num).zfill(8))
        print("Read image : ", img_file)
        img = cv2.imread(img_file, cv2.IMREAD_COLOR)
        images[cam_id] = img

    return hd_cameras, images

import math
def convert_nerf_data(images, hd_cameras):
    seed=42
    out_dir = Path("./data/converted_panoptic/images")
    out_dir.mkdir(parents=True, exist_ok=True)

    all_frames = []
    for i, cam in enumerate(hd_cameras):
        # 1. 이미지 저장
        img = images[i]
        img_out_path = out_dir / f"{i:03d}.png"
        cv2.imwrite(str(img_out_path), img)

        # 2. pose 변환 (camera-to-world)
        R = cam['R']
        t = cam['t']
        RT = np.concatenate([R, t], axis=1)  # [3x4]
        RT_h = np.vstack([RT, np.array([[0, 0, 0, 1]])])  # [4x4]
        c2w = np.linalg.inv(RT_h)

        # 3. frame info 저장
        all_frames.append({
            "file_path": f"images/{i:03d}",
            "transform_matrix": c2w.tolist()
        })

    # 4. 카메라 intrinsic → FOV 계산
    H, W = img.shape[:2]
    focal = cam['K'][0, 0]
    camera_angle_x = float(2 * np.arctan(W / (2 * focal)))
    print("[1] H, W, focal:", H, W, focal)
    print("[1] imgs.shape:", img.shape)
    print("[1] camera_angle_x:", camera_angle_x)

    # 5. 인덱스 섞어서 train/val/test 분할
    N = len(all_frames)
    indices = np.arange(N)
    np.random.seed(seed)
    np.random.shuffle(indices)

    train_split = int(0.8 * N)
    val_split = int(0.9 * N)

    idx_train = indices[:train_split]
    idx_val = indices[train_split:val_split]
    idx_test = indices[val_split:]

    splits = {
        "train": idx_train,
        "val": idx_val,
        "test": idx_test
    }

    # 6. 각각 json으로 저장
    for split_name, split_indices in splits.items():
        frames = [all_frames[i] for i in split_indices]
        json_out = {
            "camera_angle_x": camera_angle_x,
            "frames": frames
        }
        json_path = Path("./data/converted_panoptic") / f"transforms_{split_name}.json"
        with open(json_path, "w") as f:
            json.dump(json_out, f, indent=2)

    print(f"Saved: {len(idx_train)} train, {len(idx_val)} val, {len(idx_test)} test frames.")


def get_rays(H, W, focal, c2w):
    i, j = torch.meshgrid(
        torch.arange(W, dtype=torch.float32),
        torch.arange(H, dtype=torch.float32),
        indexing='ij'
    )
    dirs = torch.stack([(i - W / 2) / focal, -(j - H / 2) / focal, -torch.ones_like(i)], -1)  # [H, W, 3]
    rays_d = torch.sum(dirs[..., None, :] * c2w[:3, :3], -1)  # [H, W, 3]
    rays_o = c2w[:3, 3].expand(rays_d.shape)  # [H, W, 3]
    return rays_o.reshape(-1, 3), rays_d.reshape(-1, 3)

def render_image(model, pose, H, W, focal, device):
    rays_o, rays_d = get_rays(H, W, focal, pose)
    rays_o = rays_o.to(device)
    rays_d = rays_d.to(device)

    N_rays = rays_o.shape[0]
    N_samples = 128
    batch_size = 1024
    rgb_output = []

    for i in range(0, N_rays, batch_size):
        ro = rays_o[i:i+batch_size]
        rd = rays_d[i:i+batch_size]

        near = 0.0
        far = 4.0

        z_vals = torch.linspace(near, far, N_samples, device=device).expand(ro.shape[0], N_samples)
        points = ro[..., None, :] + rd[..., None, :] * z_vals[..., :, None]

        view_dir = F.normalize(rd, dim=-1)
        view_enc = positional_encoding(view_dir, L=4)
        view_enc_repeated = view_enc[:, None, :].expand(-1, N_samples, -1).reshape(-1, view_enc.shape[-1])

        points_flat = points.reshape(-1, 3)
        pos_enc = positional_encoding(points_flat, L=10)

        raw = model(pos_enc, view_enc_repeated).view(ro.shape[0], N_samples, 4)
        # raw[..., 3] = torch.relu(raw[..., 3])
        sigma = F.softplus(raw[..., 3])
        raw = torch.cat([raw[..., :3], sigma.unsqueeze(-1)], dim=-1)


        rgb = volume_rendering(raw, z_vals)
        rgb_output.append(rgb.detach().cpu())

    rgb_output = torch.cat(rgb_output, dim=0)
    rgb_img = rgb_output.view(H, W, 3).numpy()
    rgb_img = (np.clip(rgb_img, 0, 1) * 255).astype(np.uint8)
    return rgb_img

from models.nerf_model import NeRF
from train.trainer import train_model
from train.loss import mse_loss

def train():
    # raw_cameras, raw_images = load_data()
    # convert_nerf_data(raw_images, raw_cameras)

    # images : [batch, height, width, 3] => RGB 이미지들
    # poses : [batch, 4, 4] => camera-to-world 변환 행렬
    # render_poses : [batch, 4, 4] => camera path
    # hwf : [height, width, focal] => h, w, f
    # i_split : [train, val, test]
    images, poses, render_poses, hwf, i_split = load_mvmp_data(datadir, half_res=True)
    print('Loaded mvmp', images.shape, render_poses.shape, hwf, datadir)
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

        rays_o, rays_d = get_rays(H, W, focal_full, pose)
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
    train_model(model, rays_o, rays_d, target_rgb, optimizer, mse_loss, N_samples=N_samples, epochs=5)

    rgb_img = render_image(model, torch.from_numpy(poses[i_train[0]]), H_full, W_full, focal_full, device)
    cv2.imwrite("rendered_train_pose.png", rgb_img)
    print("Rendered image shape:", rgb_img)
    original = (images[idx] * 255).astype(np.uint8)
    cv2.imwrite("original_reference.png", original)

    torch.save(model.state_dict(), "logs/nerf_mvmp.pt")
    print("✅ 모델 저장 완료!")


from tqdm import tqdm

def eval() :
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    print("Using device:", device)

    # Load the model
    model = NeRF(L_pos=10, L_dir=4, hidden_dim=256).to(device)
    model.load_state_dict(torch.load("logs/nerf_mvmp.pt"))
    # Load data
    images, poses, render_poses, hwf, i_split = load_mvmp_data(datadir, half_res=True)
    print('Loaded mvmp', images.shape, render_poses.shape, hwf, datadir)
    i_train, i_val, i_test = i_split

    H_full, W_full, focal_full = map(int, hwf)

    # 렌더된 프레임 저장 폴더
    os.makedirs("logs", exist_ok=True)

    # 🎞️ MP4로 저장
    out = cv2.VideoWriter("rendered_video.mp4", cv2.VideoWriter_fourcc(*'mp4v'), 30, (W_full, H_full))

    # render_poses 순회

    for i, pose in tqdm(enumerate(render_poses), desc="Rendering poses", total=len(render_poses)):
        rgb_img = render_image(model, pose, H_full, W_full, focal_full, device)
        out.write(rgb_img)

    out.release()
    print("Video saved as rendered_video.mp4 ✅")

if __name__ == '__main__':
    train()
    eval()

