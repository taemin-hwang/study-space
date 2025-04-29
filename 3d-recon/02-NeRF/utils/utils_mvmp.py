import os
import torch
import numpy as np
import imageio
import json
import torch.nn.functional as F
import cv2

trans_t = lambda t : torch.Tensor([
    [1,0,0,0],
    [0,1,0,0],
    [0,0,1,t],
    [0,0,0,1]]).float()

rot_phi = lambda phi : torch.Tensor([
    [1,0,0,0],
    [0,np.cos(phi),-np.sin(phi),0],
    [0,np.sin(phi), np.cos(phi),0],
    [0,0,0,1]]).float()

rot_theta = lambda th : torch.Tensor([
    [np.cos(th),0,-np.sin(th),0],
    [0,1,0,0],
    [np.sin(th),0, np.cos(th),0],
    [0,0,0,1]]).float()


def pose_spherical(theta, phi, radius):
    c2w = trans_t(radius)
    c2w = rot_phi(phi/180.*np.pi) @ c2w
    c2w = rot_theta(theta/180.*np.pi) @ c2w
    c2w = torch.Tensor(np.array([[-1,0,0,0],[0,0,1,0],[0,1,0,0],[0,0,0,1]])) @ c2w
    return c2w

def load_data(basedir, half_res=False, testskip=1):
    import os, json, cv2
    import numpy as np
    import torch

    splits = ['train', 'val', 'test']
    metas = {}
    for s in splits:
        with open(os.path.join(basedir, 'transforms_{}.json'.format(s)), 'r') as fp:
            metas[s] = json.load(fp)

    all_imgs = []
    all_poses = []
    counts = [0]

    for s in splits:
        meta = metas[s]
        imgs = []
        poses = []
        if s == 'train' or testskip == 0:
            skip = 1
        else:
            skip = testskip

        for frame in meta['frames'][::skip]:
            fname = os.path.join(basedir, frame['file_path'] + '.png')
            img = cv2.imread(fname, cv2.IMREAD_UNCHANGED)

            if img.shape[2] == 3:
                img = cv2.cvtColor(img, cv2.COLOR_RGB2RGBA)
            elif img.shape[2] == 4:
                pass  # already RGBA

            img = img.astype(np.float32) / 255.0
            imgs.append(img)
            poses.append(np.array(frame['transform_matrix']))

        imgs = np.array(imgs).astype(np.float32)
        poses = np.array(poses).astype(np.float32)
        counts.append(counts[-1] + imgs.shape[0])
        all_imgs.append(imgs)
        all_poses.append(poses)

    i_split = [np.arange(counts[i], counts[i + 1]) for i in range(3)]
    imgs = np.concatenate(all_imgs, 0)
    poses = np.concatenate(all_poses, 0)

    ### [NEW] 월드 좌표계 정규화
    # 1. 카메라 중심 위치만 추출
    cam_centers = poses[:, :3, 3]
    scene_center = np.mean(cam_centers, axis=0)
    poses[:, :3, 3] -= scene_center

    # 2. 정규화 스케일 계산 (가장 멀리 있는 카메라까지 1.0이 되도록)
    max_dist = np.max(np.linalg.norm(poses[:, :3, 3], axis=-1))
    poses[:, :3, 3] /= max_dist

    ### 화면 정보
    H, W = imgs[0].shape[:2]
    camera_angle_x = float(meta['camera_angle_x'])
    focal = .5 * W / np.tan(.5 * camera_angle_x)
    print("[2] H, W, focal:", H, W, focal)

    ### 렌더링용 포즈
    render_poses = torch.stack(
        [pose_spherical(angle, -30.0, 4.0) for angle in np.linspace(-180, 180, 40 + 1)[:-1]],
        0
    )

    if half_res:
        H = H // 2
        W = W // 2
        focal = focal / 2

        imgs_half_res = np.zeros((imgs.shape[0], H, W, 4))
        for i, img in enumerate(imgs):
            imgs_half_res[i] = cv2.resize(img, (W, H), interpolation=cv2.INTER_AREA)
        imgs = imgs_half_res

    return imgs, poses, render_poses, [H, W, focal], i_split

import torch
import numpy as np
import imageio
import json
import os
import cv2
import torch.nn.functional as F
from pathlib import Path
from utils.positional_encoding import positional_encoding, volume_rendering

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
