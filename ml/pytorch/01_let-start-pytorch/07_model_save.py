# HOW TO SAVE AND LOAD MODELS

import torch
import torchvision.models as models

model = models.vgg16(pretrained=True)

## pytoch 모델은 학습한 매개변수를 state_dict라고 불리는 내부 상태 사전에 저장할 수 있음
torch.save(model.state_dict(), 'model_weights.pth')

model = models.vgg16() # 기본 가중치를 불러오지 않음, 기본 구조는 가져옴 (e.g. Fc->pooling->Fc->pooling 등)
model.load_state_dict(torch.load('model_weights.pth'))

## 추론 (inference)를 하기 전에 eval() 메소드를 호출하여 평가보드로 설정
model.eval()

# 모델의 형태를 포함하여 저장하고 불러오기
torch.save(model, 'model.pth')
model = torch.load('model.pth')
