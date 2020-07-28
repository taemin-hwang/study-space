# NOTE
# DICT : {}
# LIST : []
# TUPLE : ()

dic = {}
dic['taemin'] = 1
dic['minji'] = 2
dic['jongwoong'] = 3
dic['yeonsoo'] = 4

print(dic['taemin'])

for x in dic.keys():
    print('%s %s' %(x, dic[x]))

myD = {10:'aa', 20:'bb',30:'cc'}
for n in myD:
    print(n, myD[n])