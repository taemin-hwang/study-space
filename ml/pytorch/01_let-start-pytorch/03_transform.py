# Transform (변형)
## 모든 데이터가 항상 머신러닝 학습에 필요한 형태로 제공되지는 않습니다
## Transform을 통해 데이터를 조작하고 학습에 적합하게 만듭니다

## 모든 torchvision 데이터셋들은 callable 매개변수 (transform과 target_transform)을 가집니다
### transform => 특징 (feature)를 변경하기 위한 callable
### target_transform => 정답 (label)을 변경하기 위한 callable

import torch
from torchvision import datasets
from torchvision.transforms import ToTensor, Lambda

ds = datasets.FashionMNIST(
    root="data",
    train=True,
    download=True,
    transform=ToTensor(),
    target_transform=Lambda(lambda y: torch.zeros(10, dtype=torch.float).scatter_(0, torch.tesnor(y), value=1))
)

## ToTensor()
### PIL image나 Numpy 배열을 FloatTensor로 변환하고*
### 이미지 픽셀의 intensity를 [0, 1] 범위로 조정* => (image/.255)랑 같은 의미인듯

## Lambda 변형
### 사용자 정의 함수를 적용하는 방법
### 예제에서는 정수를 원-핫 인코딩 텐서로 바꾸는 함수를 정의하였음
### 크기 10짜리 0 tensor를 만들고 scatter_를 호출해서 정답 y에 해당하는 인덱스에 value 1을 할당함