def hap(x, y):
    return x + y


print(hap(10, 20))
print((lambda x, y : x + y)(10, 20))

# map(function, list)
a = map(lambda x : x ** 2, range(5))
print(a)


