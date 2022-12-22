import torch
import numpy as np

### 랜덤 또는 상수 텐서 만들기
shape = (2, 3,)
rand_tensor = torch.rand(shape)
ones_tensor = torch.ones(shape)
zeros_tensor = torch.zeros(shape)

print(f"random tensor: \n{rand_tensor} \n")
print(f"ones tensor: \n{ones_tensor} \n")
print(f"zeros tensor: \n{zeros_tensor} \n")

# 텐서 연산 (Operation)
tensor = torch.rand(3, 4)

if torch.cuda.is_available():
    tensor = tensor.to('cuda')

### Numpy 식 인덱싱과 슬라이싱
tensor = torch.ones(4, 4)
tensor[:, 1] = 0
print(tensor)

### 텐서 합치기
t1 = torch.cat([tensor, tensor, tensor], dim=1)
print(t1)

### 텐서 곱하기 (요소별 곱; element-wise product)
print(f"tensor.mul(tensor) \n {tensor.mul(tensor)} \n")
print(f"tensor * tensor \n {tensor*tensor}")

### 텐서 행렬곱
print(f"tensor.matmul(tensor) \n{tensor.matmul(tensor)} \n")
print(f"tensor @ tensor \n {tensor@tensor}")

### 바꿔치기 연산 (in-place)
# _접미사를 갖는 연산들은 바꿔치기 연산입니다, x.copy_()나 x.t_()는 x를 변경합니다 (deep-copy후 반환이 아니라)
print(tensor, "\n")
tensor.add_(5)
print(tensor)
