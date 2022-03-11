import numpy as np

out = [[1, 2, 3, 0.1],
       [1, 2, 3, 0.1],
       [1, 2, 3, 0.1]]

npout = np.array(out)

#print(npout[:, 0])
#print(npout[:, 1])
#print(npout[:, 2])
#print(npout[:, 3])
#npout[:, 3][npout[:, 3] < 0.7] = 0

buffer_size = 5

arr = []
for i in range(buffer_size):
    for j in range(len(out)):
        npout[j, 0] = (j)*(i+1)
        npout[j, 1] = (j+1)*(i+1)
        npout[j, 2] = (j+2)*(i+1)
    npout[:, 3] = 0.1*(i+1)
    arr.append(npout.copy())

nparr = np.array(arr)

print(nparr)


print(nparr.shape[0])

#print(nparr[:, 0, :])
#print(nparr[:, 1, :])
#print(nparr[:, 2, :])

ret = np.zeros(npout.shape)
for i in range(len(out)):
    #print(nparr[:, i, :])
    #nose
    parsed = nparr[:, i, :]
    xdata = parsed[:, 0]
    ydata = parsed[:, 1]
    zdata = parsed[:, 2]
    confidence = parsed[:, 3]
    print(xdata)
    print(ydata)
    print(zdata)
    #print(confidence.astype(int))

    #print(confidence.astype(int))
    x_avg = np.average(xdata, weights=confidence)#.astype(int))
    y_avg = np.average(ydata, weights=confidence)#.astype(int))
    z_avg = np.average(zdata, weights=confidence)#.astype(int))
    c_avg = np.average(confidence, weights=confidence)#.astype(int))

    print('x avg: ', x_avg)
    print('y avg: ', y_avg)
    print('z avg: ', z_avg)
    print('c avg: ', c_avg)
    print('-----------------------')

    ret[i] = [x_avg, y_avg, z_avg, c_avg]

print(ret)
