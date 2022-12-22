# Introduction to torch.autograd

## 배경
# 신경망은 어떤 입력 데이터에 대해 실행되는 중첩된 함수들의 모음입니다.
# 이 합수들은 tensor로 저장되는 (weight, bias)로 구성된 매개변수로 정의됩니다.
# 신경망 학습은 2단계로 이루어집니다

## 순전파 (forward propagation)
# 신경망은 정답을 맞추기 위해 최선의 추측을 합니다
## 역전파 (backward propagation)
# 순전파를 통해 추측한 결과와 실제 값을 비교해 발생한 오류를 이용해 매개변수를 적절히 조절합니다
# 출력으로부터 역방향으로 이동하면서 오류에 대한 함수들의 매개변수들의 미분값을 수집하고
# 경사하강법을 사용해 매개변수들을 최적화 합니다

import torch, torchvision

model = torchvision.models.resnet18(pretrained=True)
data = torch.rand(1, 3, 64, 64)
labels = torch.rand(1, 1000)

prediction = model(data) # 순전파
loss = (prediction - labels).sum()
loss.backward() # 역전파

optim = torch.optim.SGD(model.parameters(), lr=1e-2, momentum=0.9)
optim.step() # 경사하강법