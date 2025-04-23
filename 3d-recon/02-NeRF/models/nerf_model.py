import torch
import torch.nn as nn
import torch.nn.functional as F

class NeRF(nn.Module):
    def __init__(self, L_pos=10, L_dir=4, hidden_dim=256):
        super(NeRF, self).__init__()

        self.L_pos = L_pos
        self.L_dir = L_dir
        in_dim_pos = 3 + 3 * 2 * L_pos
        in_dim_dir = 3 + 3 * 2 * L_dir

        # 위치 입력 처리 (x)
        self.fc1 = nn.Sequential(
            nn.Linear(in_dim_pos, hidden_dim),
            nn.ReLU(),
            nn.Linear(hidden_dim, hidden_dim),
            nn.ReLU(),
            nn.Linear(hidden_dim, hidden_dim),
            nn.ReLU()
        )

        # sigma 예측 (density)
        self.fc_sigma = nn.Linear(hidden_dim, 1)

        # 색상 예측을 위해 direction도 추가 입력
        self.fc_feature = nn.Linear(hidden_dim, hidden_dim)
        self.fc_rgb = nn.Sequential(
            nn.Linear(hidden_dim + in_dim_dir, hidden_dim // 2),
            nn.ReLU(),
            nn.Linear(hidden_dim // 2, 3)
        )

    def forward(self, x_enc, d_enc):
        h = self.fc1(x_enc)
        sigma = self.fc_sigma(h)

        feature = self.fc_feature(h)
        h_combined = torch.cat([feature, d_enc], dim=-1)
        rgb = self.fc_rgb(h_combined)

        return torch.cat([rgb, sigma], dim=-1)  # [B, 4]