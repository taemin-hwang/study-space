# 신경망
## 신경망은 torch.nn 패키지를 사용하여 생성할 수 있음

# 신경망의 일반적인 학습 과정
## 학습 가능한 매개변수를 갖는 신경망을 정의 (=설계)
## 데이터셋 입력을 반복
## 입력을 신경망에서 전파
## 손실을 계산
## 변화도를 신경망의 매개변수들에 역으로 전파
## 신경망의 가중치를 갱신 (새로운 가중치 = 기존 가중치 - 학습률 * 변화도)

# 신경망 정의하기

import torch
import torch.nn as nn
import torch.nn.functional as F

class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        # 입력 이미지 채널 1개, 출력 채널 6개, 5x5의 정사각 컨볼루션 행렬
        self.conv1 = nn.Conv2d(1, 6, 5)
        self.conv2 = nn.Conv2d(6, 16, 5)
        # 아핀 (affine) 연산: y = Wx + b
        self.fc1 = nn.Linear(16 * 5 * 5, 120)
        self.fc2 = nn.Linear(120, 84)
        self.fc3 = nn.Linear(84, 10)

    def forward(self, x):
        x = F.max_pool2d(F.relu(self.conv1(x)), (2,2))
        x = F.max_pool2d(F.relu(self.conv2(x)), 2)
        x = torch.flatten(x, 1)
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = self.fc3(x)
        return x

net = Net()

params = list(net.parameters())
print(len(params))
print(params[0].size())  # conv1의 .weight

input = torch.randn(1, 1, 32, 32)
out = net(input)
print(out)

net.zero_grad()
out.backward(torch.rand(1, 10))

# 손실 함수 (loss function)
## 예측 값 (prediction)이 정답 (ground-truth)랑 얼마나 다른지 계산

output = net(input)
target = torch.randn(10)
target = target.view(1, -1)
criterion = nn.MSELoss()

loss = criterion(output, target)
print(loss)

print(loss.grad_fn)  # MSELoss
print(loss.grad_fn.next_functions[0][0])  # Linear
print(loss.grad_fn.next_functions[0][0].next_functions[0][0])  # ReLU

# 역전파 (back-propagation)
## 오차를 역전파 하기 위해서는 loss.backward()만 해주면 끝입니다
## 기존에 계산된 변화도 값을 누적하지 않기 위해 변화도를 항상 0으로 만들어야 합니다

net.zero_grad()

print('conv1.bias.gard before backward')
print(net.conv1.bias.grad)

loss.backward()

print('conv1.bias.grad after backward')
print(net.conv1.bias.grad)

# 가중치 갱신 (Upate weight)

learning_rate = 0.01
# for f in net.parameters():
#     f.data.sub_(f.grad.data * learning_rate)

import torch.optim as optim

optimizer = optim.SGD(net.parameters(), lr=0.01)

optimizer.zero_grad()
output = net(input)
loss = criterion(output, target)
loss.backward()
optimizer.step()