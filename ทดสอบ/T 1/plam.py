import math
import matplotlib.pyplot as plt
import time
import numpy as np
o = open('A1.txt', 'r')
fig, bx = plt.subplots()

bx.axis([0, 500, -100, 100])
x1 = []





for line in o.read().split('\n'):
    if not(len(line)==0):
        #data = line.split()
        s = float(line)
        a = ('%.2f'%s)
        x1.append(str(a))
        
    else:
        break



linex = bx.plot(x1)


fig.canvas.manager.show()


linex[0].set_ydata(x1)


fig.canvas.draw()
fig.canvas.flush_events()





o.close()
