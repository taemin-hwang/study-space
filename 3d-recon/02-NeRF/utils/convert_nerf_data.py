import json
import numpy as np
import os
import cv2
from pathlib import Path
import torch
import torch.nn.functional as F

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

    K_target = hd_cameras[0]['K']
    dist_coeffs = np.zeros((4, 1))

    all_frames = []
    for i, cam in enumerate(hd_cameras):
        # 1. 이미지 저장
        img = images[i]
        h, w = img.shape[:2]
        K_orig = cam['K']
        map1, map2 = cv2.initUndistortRectifyMap(K_orig, dist_coeffs, None, K_target, (w, h), 5)
        img = cv2.remap(img, map1, map2, interpolation=cv2.INTER_LINEAR)

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

    train_split = int(0.9 * N)
    val_split = int(0.95 * N)

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
