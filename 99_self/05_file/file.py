import os

path = os.getcwd() + '/99_self/05_file/readme'

f = open(path)
print(f.readline())
print(f.readline())