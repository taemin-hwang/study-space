import torch
import os
import cv2
import json
import numpy as np
from pathlib import Path

from torch.utils.data import DataLoader, TensorDataset
from models.nerf_model import NeRF
from utils.convert_nerf_data import convert_nerf_data, load_data
from train.train import train
from train.loss import mse_loss
from utils.positional_encoding import positional_encoding, volume_rendering
# from utils.render_image import get_rays, render_image
from utils import utils_blender # import load_blender, get_rays
from utils import utils_mvmp # import load_mvmp, get_rays
import torch.nn as nn
import torch.nn.functional as F

basedir = "./logs"
expname = "mvmp_panoptic"
# datadir = "./data/converted_panoptic"
datadir = "./data/nerf_synthetic/lego"
dataset_type = "blender"

from tqdm import tqdm
def eval() :
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    print("Using device:", device)

    # Load the model
    model = NeRF(L_pos=10, L_dir=4, hidden_dim=256).to(device)
    model.load_state_dict(torch.load("best_model.pth"))

    # Load data
    if datadir == "./data/nerf_synthetic/lego":
        images, poses, render_poses, hwf, i_split = utils_blender.load_data(datadir, half_res=True)
    elif datadir == "./data/converted_panoptic":
        images, poses, render_poses, hwf, i_split = utils_mvmp.load_data(datadir, half_res=True)
    else:
        raise ValueError("Unsupported dataset type")

    print('Loaded mvmp', images.shape, render_poses.shape, hwf, datadir)

    i_train, i_val, i_test = i_split
    H_full, W_full, focal_full = map(int, hwf)

    if datadir == "./data/nerf_synthetic/lego":
        rgb_img = utils_blender.render_image(model, torch.from_numpy(poses[i_test[0]]), H_full, W_full, focal_full, device)
    elif datadir == "./data/converted_panoptic":
        rgb_img = utils_mvmp.render_image(model, torch.from_numpy(poses[i_test[0]]), H_full, W_full, focal_full, device)
    else:
        raise ValueError("Unsupported dataset type")

    cv2.imwrite("rendered_train_pose.png", rgb_img)

    os.makedirs("logs", exist_ok=True)
    out = cv2.VideoWriter("rendered_video.mp4", cv2.VideoWriter_fourcc(*'mp4v'), 30, (W_full, H_full))

    for i, pose in tqdm(enumerate(render_poses), desc="Rendering poses", total=len(render_poses)):
        if datadir == "./data/nerf_synthetic/lego":
            rgb_img = utils_blender.render_image(model, pose, H_full, W_full, focal_full, device)
        elif datadir == "./data/converted_panoptic":
            rgb_img = utils_mvmp.render_image(model, pose, H_full, W_full, focal_full, device)
        else:
            raise ValueError("Unsupported dataset type")
        out.write(rgb_img)

    out.release()
    print("Video saved as rendered_video.mp4 ✅")

if __name__ == '__main__':
    # raw_cameras, raw_images = load_data()
    # convert_nerf_data(raw_images, raw_cameras)

    train(datadir)
    eval()