import torch
from torch.utils.data import Dataset
from torchvision import datasets
from torchvision.transforms import ToTensor
import matplotlib.pyplot as plt

training_data = datasets.FashionMNIST(
    root="data", #데이터가 저장되는 경로
    train=True,  # 학습용 데이터셋 여부
    download=True, # root에 데이터가 없는 경우 인터넷에서 다운로드
    transform=ToTensor()
)

test_data = datasets.FashionMNIST(
    root="data",
    train=False,
    download=True,
    transform=ToTensor()
)

## 데이터를 순회하고 시각화하기
labels_map = {
    0: "T-Shirt",
    1: "Trouser",
    2: "Pullover",
    3: "Dress",
    4: "Coat",
    5: "Sandal",
    6: "Shirt",
    7: "Sneaker",
    8: "Bag",
    9: "Ankle Boot",
}

figure = plt.figure(figsize=(8, 8))
cols, rows = 3, 3
for i in range(1, cols * rows + 1):
    sample_idx = torch.randint(len(training_data), size=(1,)).item()
    img, label = training_data[sample_idx]
    figure.add_subplot(rows, cols, i)
    plt.title(labels_map[label])
    plt.axis("off")
    plt.imshow(img.squeeze(), cmap="gray")
plt.savefig('fig1.png')

# 파일에서 사용자 정의 데이터셋 만들기
## 사용자 정의 Dataset 클래스는 반드시 3개 함수를 구현해야 함
### __init__, __len__, __getitem__

import os
import pandas as pd
from torchvision.io import read_image

class CustomImageDataset(Dataset): # Dataset 클래스를 상속받음
    def __init__(self, annotations_file, img_dir, transform=None, target_transform=None):
        self.img_labels = pd.read_csv(annotations_file, names=['file_name', 'label'])
        self.img_dir = img_dir
        self.transform = tranform
        self.target_transform = target_transform

    def __len__(self):
        return len(self.img_labels)

    def __getitem__(self, idx):
        img_path = os.path.join(self.img_dir, self.img_labels.iloc[idx, 0])
        image = read_image(img_path)
        label = self.img_labels.iloc[idx, 1]
        if self.transform:
            image = self.transform(image)
        if self.target_transform:
            lebel = self.target_transform(label)
        return image, label

# DataLoader로 학습용 데이터 준비하기
## Dataset은 feature를 가져와 label을 지정하는 일을 한 번에 합니다
## 모델을 학습할 때 샘플들을 minibatch로 전달하고
## 매 epoch마다 데이터를 다시 섞어 overfit을 막고
## 파이썬의 multiprocessing을 사용하여 데이터 검색 속도를 높이려고 합니다

from torch.utils.data import DataLoader

train_dataloader = DataLoader(training_data, batch_size=64, shuffle=True)
test_dataloader = DataLoader(test_data, batch_size=64, shuffle=True)

train_features, train_labels = next(iter(train_dataloader))
print(f"Feature batch shape: {train_features.size()}")
print(f"Labels batch shape: {train_labels.size()}")
img = train_features[0].squeeze()
label = train_labels[0]

figure = plt.figure(figsize=(8, 8))
plt.imshow(img, cmap="gray")
plt.savefig('fig2.png')
print(f"Label: {label}")