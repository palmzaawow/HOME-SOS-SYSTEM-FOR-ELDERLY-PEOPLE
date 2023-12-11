import math
import matplotlib.pyplot as plt
import time
import numpy as np
import peakutils
o = open('G1.txt', 'r')
fig, bx = plt.subplots()
fig2, ax = plt.subplots(4,1)
for x in ax:
    x.axis([0, 3500, -10, 10])
bx.axis([0, 3500, -10, 10])
x1 = []
y1 = []
z1 = []
h1 = []


#fig.canvas.manager.show()
#fig2.canvas.manager.show() 

for line in o.read().split('\n'):
    if not(len(line)==0):
        #w.write(line)
        #w.write('\n')
        #print(line.split(''))
        data = line.split()
        x = float(data[0])
        y = float(data[1])
        z = float(data[2])
        h = math.sqrt(x**2+y**2+z**2)
        x1.append(x)
        y1.append(y)
        z1.append(z)
        h1.append(h)
    else:
        break

x11 = np.array(x1)
peaksX = peakutils.indexes(x11, thres=0.7, min_dist=200)
print(peaksX)
print(x11[peaksX])
y11 = np.array(y1)
peaksY = peakutils.indexes(y11, thres=0.7, min_dist=200)
print(peaksY)
print(y11[peaksY])
z11 = np.array(z1)
peaksZ = peakutils.indexes(z11, thres=0.7, min_dist=200)
print(peaksZ)
print(z11[peaksZ])
h11 = np.array(h1)
peaksH = peakutils.indexes(h11, thres=0.7, min_dist=200)
print(peaksH)
print(h11[peaksH])

linex = bx.plot(x1)
liney = bx.plot(y1)
linez = bx.plot(z1)
linew = bx.plot(h1)
linex1 = ax[0].plot(x1)
liney2 = ax[1].plot(y1)
linez3 = ax[2].plot(z1)
linew4 = ax[3].plot(h1)


fig.canvas.manager.show()
fig2.canvas.manager.show()

linex[0].set_ydata(x1)
liney[0].set_ydata(y1)  
linez[0].set_ydata(z1)
linew[0].set_ydata(h1)
linex1[0].set_ydata(x1)
liney2[0].set_ydata(y1)
linez3[0].set_ydata(z1)
linew4[0].set_ydata(h1)


fig.canvas.draw()
fig.canvas.flush_events()
fig2.canvas.draw()
fig2.canvas.flush_events()
print(np.max(x1))
print(np.max(y1))
print(np.max(z1))
print(np.max(h1))



o.close()
