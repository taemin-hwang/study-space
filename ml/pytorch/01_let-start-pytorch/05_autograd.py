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

 # z는 예측값이고, y는 실제 ground-truth에 해당
 # loss를 cross_entropy를 통해 계산
loss = torch.nn.functional.binary_cross_entropy_with_logits(z, y)

 ## 손실함수의 변화도를 계산하기 위해 텐서에 requires_grad 속성을 설정
print(f"gradient function for z = {z.grad_fn}")
print(f"gradient function for loss = {loss.grad_fn}")

# 변화도 (Gradient) 계산하기
 ## 신경망에서 매개변수의 가중치를 최적화하려면 매개변수에 대한 손실함수의 도함수 (derivative)를 계산해야 합니다
 ## 즉 d(loss)/d(w)와 d(loss)/d(b)가 필요합니다
 ## 이러한 도함수를 계산하기 위해 loss.backward()를 호출한뒤 w.grad와 b.grad에서 값을 가져옵니다

loss.backward()
print(w.grad)
print(b.grad)
 ## 성능 상의 이유로, 주어진 그래프에서 backward를 사용한 변화도 계산은 한 번만 수행할 수 있습니다
 ## 마약 동일한 그래프에서 여러번의 backward 호출이 필요하면 backward 호출 시에 retain_graph=True를 전달해야 합니다


# 변화도 추적 멈추기
 ## 기본적으로 requires_grad=True인 모든 텐서들은 연산 기록을 추적하고 변화도 계산을 지원함
 ## 그러나 모델을 학습한 뒤 입력 데이터를 적용하기만 하는 (완성된 모델) 경우처럼 '순전파' 연산만 필요한 경우
 ## 이러한 변화도 추적 지원이 필요없을 수 있습니다
 ## 연산 코드를 torch.no_grad() 블록으로 둘러싸서 연산 추적을 멈출 수 있습니다

z = torch.matmul(x, w)+b
print(z.requires_grad)

with torch.no_grad():
    z = torch.matmul(x, w)+b
print(z.requires_grad)

 ## 동일한 결과를 얻는 또 다른 방법은 detach() 메소드를 사용하는 것입니다
z = torch.matmul(x, w)+b
z_det = z.detach()
print(z.requires_grad)

 ## 변화도 추적을 멈춰야 하는 이유
  ### 신경망의 일부 매개변수를 고정된 매개변수 (frozen parameter)로 표시 (사전 학습된 신경망을 미세조정해야 할 때)
  ### 변화도를 추적하지 않는 연산이 더 효율적이기 때문에, forward propagation만 할 때는 연산 속도가 향상됨

# 연산 그래프에 대한 추가 정보
 ## 개념적으로