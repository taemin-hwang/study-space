# Optimize parameters
 ## 모델과 데이터가 준비되었으면, 매개변수를 최적화하여 모델을 학습하고, 검증하고, 테스트할 차례입니다
 ## 모델 학습 과정은 반복적인 과정을 거칩니다 (epoch)
 ## 각 epoch에서 모델은 출력을 추측하고, 추측과 ground-truth 사이의 오류 (loss)를 계산하고
 ## 오류의 도합수 (derivative)를 수집한뒤
 ## 경사하강법을 사용해 파라미터를 최적화 (optimize)합니다

# 기본 (pre-requisite) 코드
import torch
from torch import nn
from torch.utils.data import DataLoader
from torchvision import datasets
from torchvision.transforms import ToTensor, Lambda

training_data = datasets.FashionMNIST(
    root="data",
    train=True,
    download=True,
    transform=ToTensor()
)

test_data = datasets.FashionMNIST(
    root="data",
    train=False,
    download=True,
    transform=ToTensor()
)

train_dataloader = DataLoader(training_data, batch_size=64)
test_dataloader = DataLoader(test_data, batch_size=64)

class NeuralNetwork(nn.Module):
    def __init__(self):
        super(NeuralNetwork, self).__init__()
        self.flatten = nn.Flatten()
        self.linear_relu_stack = nn.Sequential(
            nn.Linear(28*28, 512),
            nn.ReLU(),
            nn.Linear(512, 512),
            nn.ReLU(),
            nn.Linear(512, 10),
        )

    def forward(self, x):
        x = self.flatten(x)
        logits = self.linear_relu_stack(x)
        return logits

model = NeuralNetwork()

# 하이퍼파라미터 (hyper-parameter)
 ## 하이퍼파라미터는 모델 최적화 과정을 제어할 수 있는 조절 가능한 매개변수입니다
 ## 서로 다른 하이퍼파라미터 값은 모델 학습과 수렴율 (convergence rate)에 영향을 미칠 수 있습니다
  ### 에폭 (epoch)수 - 데이터셋을 반복하는 횟수
  ### 배치 크기 (batch size) - 매개변수가 갱신되기 전 신경망을 통해 전파된 데이터 샘플의 수
  ### 학습률 (learning rate) - 각 배치/에폭에서 모델의 매개변수를 조절하는 비율, 값이 작을 수록 학습속도가 느려짐

learning_rate = 1e-3
batch_size = 64
epochs = 5

# 최적화 단계 (Optimization loop)
 ## 하이퍼파라미터를 설정한 뒤에는 최적화 단계를 통해 모델을 학습하고 최적화 할 수 있습니다
 ## 하나의 에폭은 다음 두 부분으로 구성됩니다
  ### 학습 단계 (train loop) - 학습용 데이터셋을 반복하고 최적의 매개변수로 수렴
  ### 검증/테스트 단계 (validation/test loop) - 모델 성능이 개선되고 있는지를 확인하기 위해 테스트 데이터 셋을 반복

 ## 손실 함수 (loss function)
  ### 손실 함수는 획등한 결과와 실제 값 사이의 틀린 정도 (degree of dissimilarity)를 측정하며
  ### 학습 중에 이 값을 최소화 하려고 함
  ### 일반적인 손실 함수에는 nn.MSELoss (MSE), nn.NLLLoss (Negative Log Likelihood), nn.CrossEntropyLoss 등

loss_fn = nn.CrossEntropyLoss()

 ## 옵티마이저 (Optimizer)
  ### 손실 미분값의 변화도를 이용해 최적의 파라미터를 구하는 과정 (경사하강법 등)

optimizer = torch.optim.SGD(model.parameters(), lr=learning_rate)
  ### 학습 단계 (loop)에서 최적화는 세단계로 이루어짐
   #### optimizer.zero_grad()를 호출하여 모델 매개변수의 변화도를 재설정
   #### 기본적으로 변화도는 더해지기 때문에 중복 계산을 막기 위해 반복할 때마다 명시적으로 재설정(0 할당)
   #### loss.backwards()를 호출하여 prediction loss를 back-propagation함
   #### 변화도를 계산한 뒤에는 optimizer.step()을 호출하여 수집된 변화도로 매개변수를 조정

# 전체 구현

def train_loop(dataloader, model, loss_fn, optimizer):
    size = len(dataloader.dataset)
    for batch, (X, y) in enumerate(dataloader):
        pred = model(X) # prediction
        loss = loss_fn(pred, y)

        # back-propagation
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        if batch % 100 == 0:
            loss = loss.item()
            current = batch * len(X)
            print(f"loss: {loss:>7f} [{current:>5d}/{size:>5d}]")

def test_loop(dataloader, model, loss_fn):
    size = len(dataloader.dataset)
    num_batches = len(dataloader)
    test_loss, correct = 0, 0

    with torch.no_grad():
        for X, y in dataloader:
            pred = model(X)
            test_loss += loss_fn(pred, y).item()
            correct += (pred.argmax(1) == y).type(torch.float).sum().item()

    test_loss /= num_batches
    correct /= size
    print(f"test error: \n Accuracy: {(100*correct):>0.1f}%, Avg loss: {test_loss:>8f} \n")

loss_fn = nn.CrossEntropyLoss()
optimizer = torch.optim.SGD(model.parameters(), lr=learning_rate)

epochs = 10
for t in range(epochs):
    print(f"Epoch {t+1}\n------------------------------------")
    train_loop(train_dataloader, model, loss_fn, optimizer)
    test_loop(test_dataloader, model, loss_fn)
print("Done")
