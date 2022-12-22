# 텐서는 배열이나 행령과 비슷한 특수한 자료구조입니다.
# PyTorch에서는 텐서를 이용해 모델의 입력과 출력, 그리고 매개변수를 인코딩합니다.
# 텐서는 GPU나 TPU에서 실행할 수 있다는 점을 제외하면 Numpy의 ndarray와 거의 동일합니다.

import torch
import numpy as np

# 텐서 초기화
## 데이터로부터 직접 생성하기 (tensor)
data = [[1,2],[3,4]]
x_data = torch.tensor(data)

## Numpy 배열로부터 생성하기 (from_numpy)
np_array = np.array(data)
x_np = torch.from_numpy(np_array)

# print(x_np)
# tensor([[1, 2],
#         [3, 4]])

# 텐서의 속성
tensor = torch.rand(3, 4)

print("shape of tensor: {}".format(tensor.shape))
print("tensor is stored on: {}".format(tensor.device))

# 텐서 연산
## transposing, indexing, slicing, 선형 대수와 같은 텐서 연산을 제공합니다
## 각 연산들은 일반적으로 CPU보다 빠른 GPU에서 실행할 수 있습니다.
if torch.cuda.is_available():
    tensor = tensor.to("cuda")
print("tensor is stored on: {}".format(tensor.device))

tensor = torch.ones(4, 4)
print("first row: {}".format(tensor[0]))
print("first column: {}".format(tensor[:,0]))
print("last column: {}".format(tensor[:,-1]))
tensor[:,1] = 0
print(tensor)
