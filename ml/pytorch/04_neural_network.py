# 신경망 모델 구성하기
## 신경망은 layer와 module로 구성되어 있음
## torch.nn 네임스페이스는 신경망을 구성하는데 필요한 모든 구성 요소를 제공함
## pytorch의 모든 모듈은 nn.Moduel의 하위 클래스에 해당함

import os
import torch
from torch import nn
from torch.utils.data import DataLoader
from torchvision import datasets, transforms

# 학습을 위한 장치 얻기
device = "cuda" if torch.cuda.is_available() else "cpu"
print("using {} device".format(device))

# 클래스 정의하기
## 신경망 모델을 nn.Module의 하위클래스로 정의하고
## nn.Module을 상속받은 모든 클래스는 forward 메소드에 입력 데이터에 대한 연산을 구현함

class NeuralNetwork(nn.Module):
    def __init__(self):
        super(NeuralNetwork, self).__init__()
        self.flatten = nn.Flatten()
        self.linear_relu_stack = nn.Sequential(
            nn.Linear(28*28, 512),
            nn.ReLU(),
            nn.Linear(512, 512),
            nn.ReLU(),
            nn.Linear(512, 10)
        )

    def forward(self, x):
        x = self.flatten(x)
        logits = self.linear_relu_stack(x)
        return logits

model = NeuralNetwork().to(device)
print(model)

X = torch.rand(1, 28, 28, device=device)
logits = model(X)
pred_probab = nn.Softmax(dim=1)(logits)
y_pred = pred_probab.argmax(1)
print("Predicted class {}".format(y_pred))

# 모델 계층 (Layer)
## FashionMNIST 모델의 계층 살펴보기
## 28*28 이미지 3개로 구성된 미니배치를 가져와서 신경망을 통과할 때 어떤 일이 발생하는지 알아본다

input_image = torch.rand(3, 28, 28)
print(input_image.size())

# nn.Flatten
## 28 X 28 이미지를 784 픽셀 값을 갖는 연속된 배열로 변환합니다

flatten = nn.Flatten()
flat_image = flatten(input_image)
print(flat_image.size())

# nn.Linear
## 저장된 weight와 bias를 사용해 선형 변환 (linear transformation)을 적용
layer1 = nn.Linear(in_features=28*28, out_features=20)
hidden1 = layer1(flat_image)
print(hidden1.size())

# nn.ReLU
## 활성 함수 (activation function)은 입력과 출력 사이에 비선형적인 관계를 만듭니다
## 비성형적 관계 형성을 통해 신경망이 다양한 현상을 학습할 수 있도록 돕습니다

print(f"before ReLU: {hidden1}\n\n")
hidden1 = nn.ReLU()(hidden1)
print(f"after ReLU: {hidden1}")

# nn.Sequential
## 순서를 갖는 모듈의 컨테이너 입니다
## 데이터는 정의된 순서로 모든 모듈들을 통해 전달됩니다

seq_modules = nn.Sequential(
    flatten,
    layer1,
    nn.ReLU(),
    nn.Linear(20, 10)
)

input_image = torch.rand(3, 28, 28)
logits = seq_modules(input_image)

# nn.Softmax
## 신경망의 마지막 선형 계층은 모델의 각 class 분류에 대한 예측 확률을 나타내도록 [0, 1]로 조정 (scale)됩니다
## dim 매개변수는 값의 합이 1이 되는 차원을 나타냅니다

softmax = nn.Softmax(dim=1)
pred_probab = softmax(logits)

# 모델 매개변수
## 신경망 내부의 많은 계층들은 매개변수화 됩니다
## nn.Module을 상속하면 모델 객체 내부의 필드가 자동으로 추정됩니다
## 모델의 parameters()와 named_parameters() 메소드로 모든 매개변수에 접근할 수 있게 됩니다

print(f"Model structure: {model} \n")

for name, param in model.named_parameters():
    print(f"layer: {name} | size: {param.size()} | value: {param[:2]} \n")