import torch
import math

def positional_encoding(x, L):
    """Sinusoidal positional encoding"""
    freq_bands = 2.0 ** torch.arange(L, device=x.device)
    out = [x]
    for freq in freq_bands:
        out.append(torch.sin(freq * x))
        out.append(torch.cos(freq * x))
    return torch.cat(out, dim=-1)  # [N, 3*2*L + 3]

def volume_rendering(rgb_sigma, z_vals):
    rgb = rgb_sigma[..., :3]  # (N_rays, N_samples, 3)
    sigma = rgb_sigma[..., 3]  # (N_rays, N_samples)
    dists = z_vals[..., 1:] - z_vals[..., :-1]
    dists = torch.cat([dists, 1e10 * torch.ones_like(dists[..., :1])], -1)  # (N_rays, N_samples)

    alpha = 1.0 - torch.exp(-sigma * dists)
    T = torch.cumprod(torch.cat([torch.ones_like(alpha[..., :1]), 1.0 - alpha + 1e-10], -1), -1)[..., :-1]
    weights = T * alpha  # (N_rays, N_samples)

    rgb_map = torch.sum(weights[..., None] * rgb, -2)
    return rgb_map