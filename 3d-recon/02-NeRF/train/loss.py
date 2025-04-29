import torch.nn.functional as F

def mse_loss(predicted, target):
    return F.mse_loss(predicted, target)
