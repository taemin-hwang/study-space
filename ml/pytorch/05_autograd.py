# torch.autograd를 사용한 자동 미분
## 신경망을 학습할 때 가장 자주 사용되는 알고리즘은 역전파 (back-propagation)입니다
## 이 알고리즘에서 모델 가중치, 편향은 손실함수의 변화도 (gradient)에 따라 조정됩니다
## 이러한 변화도를 계산하기 위해 pytorch에서는 torch.autograd라는 자동 미분 엔진이 있습니다

import torch

x = torch.ones(5) # input tensor
y = torch.zeros(3) # expected tensor
w = torch.randn(5, 3, requires_grad=True)
b = torch.randn(3, requires_grad=True)
z = torch.matmul(x, w)+b # z = w * x + b
loss = torch.nn.functional.binary_corss_entropy_with_logits(z, y)