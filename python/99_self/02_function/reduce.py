from functools import reduce

a = reduce(lambda x, y : x + y, range(5))
print(a)
