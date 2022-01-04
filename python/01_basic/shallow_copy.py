import pandas as pd
df1 = pd.DataFrame({'a': [1, 2, 3], 'b': [4, 5, 6], 'c': [7, 8, 9]})
print(df1)
print(' ')

df2 = df1 # shallow copy
print(df2)
print(' ')

df1.columns = ['d', 'e', 'f']

print(df1)
print(' ')

print(df2)
print(' ')

d1 = {'a': [1, 2, 3], 'b': [4, 5, 6], 'c': [7, 8, 9]}
d2 = d1

d1['a'] = [2, 3, 4]
print(d1)
print(d2)
