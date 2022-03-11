import numpy as np

out = [[1, 2, 3, 0.1],
       [2, 3, 4, 0.1],
       [3, 4, 5, 0.1]]

print(out)
print('---------------')

out = np.roll(out, -1, axis=0)
print(out)
print('---------------')

out[2] = [4, 5, 6, 0.1]
print(out)
print('---------------')

out = np.roll(out, -1, axis=0)
print(out)
print('---------------')

out[2] = [5, 6, 7, 0.1]
print(out)
print('---------------')
