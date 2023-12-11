import serial
import struct
import re
import math
import time   
import matplotlib.pyplot as plt
import numpy as np

fig, bx = plt.subplots()
fig2, ax = plt.subplots(4,1)   ### ขนาดกราฟ เเละจำนวนกราฟ
fig3, cx = plt.subplots()

for x in ax:
    x.axis([0, 100, -10, 10])  ### ขนาดกราฟ  limit
bx.axis([0, 100, -10, 10])
cx.axis([0, 100, -10, 10])
y = [0]*100          ###ตัวเเปร ใส่ค่า y
w = [0]*100
x = [0]*100
z = [0]*100
G = [0]*100
i = 0
lineG = cx.plot(G, label='Average')
linex = bx.plot(x, label='x axis')          #### พร็อตกราฟ x ตัวเเปร x
liney = bx.plot(y, label='y axis')
linez = bx.plot(z, label='z axis')
linew = bx.plot(w, label='ALL')
linex1 = ax[0].plot(x, label='x axis')
liney2 = ax[1].plot(y, label='y axis')
linez3 = ax[2].plot(z, label='z axis')
linew4 = ax[3].plot(w, label='ALL')

ax[0].legend()
ax[1].legend()
ax[2].legend()
ax[3].legend()
bx.legend()
cx.legend()
fig.canvas.manager.show()         ### เเสดงกราฟ
fig2.canvas.manager.show()
fig3.canvas.manager.show()
ser = serial.Serial()
ser.port = "COM5"                  ###เชื่อมพร็อตคอม com 6
ser.baudrate = 115200             ###ตั้ง 115200
ser.timeout = 0.001               ###เวลา 
ser.writeTimeout = 1

if not ser.isOpen():               ####ทดสอบcom 6  เชื่อมต่อ
    print ("123")
    ser.open()
    
else:
    print (456)

if ser.isOpen():
    print ("Serial com is opened")
    old = time.time()
    t_plot = time.time()
    o = open('mm03.txt', 'w')####เปิด notepad
    v = open('Amm03.txt', 'w')
    old = time.time()
    while True:
        msg = ser.readline()
        ##print(msg)
        if len(msg)>0:
            msg = str(msg)
            m = msg.split('\\t')
            
            if len(m)==3:
                f = float(m[1]) #ตัวที่ 2
                #p = m[0]
                #k = (p[2:7]) #ตัวที่ 1 k

                k = m[0].strip("b'")
                if len(k) >= 4 :
                    try:
                        u = float(k)
                        HO = 0
                   
                    except ValueError:
                        HO = 1
                        continue
                a = m[2]
                try:
                    c = float(a.strip('\\r\\n\''))###ตัวที่ 3
                    HO = 0
                except ValueError:
                    HO = 1
                    continue
                
                if HO == 0 :
                    if len(k) >= 4 :
                        h = math.sqrt((u)**2+float(f)**2+(c)**2)   ####  ผลรวม
                        o.write(str(k) + ' ' + str(f) +' '+str(c)+ '\n')
                        if i == 0:
                            L = (h+(w[99])*10)/11
                        if i > 0 : 
                            L = (h+(G[99])*10)/11
                            io = str(L)
                            v.write(io+ '\n')
                        i += 1
                   # if h > 15 :
                   #     print(msg)
                
                G.append(L)
                x.append(u)                     #ใส่ค่า  k  ใน array x
                y.append(f)
                z.append(c)
                w.append(h)
                G.remove(G[0])
                x.remove(x[0])
                y.remove(y[0])
                z.remove(z[0])
                w.remove(w[0])
                lineG[0].set_ydata(G)
                linex[0].set_ydata(x)               # ใส่ตัวเเปร x ใน เส้น x
                liney[0].set_ydata(y)
                linez[0].set_ydata(z)
                linew[0].set_ydata(w)
                linex1[0].set_ydata(x)
                liney2[0].set_ydata(y)
                linez3[0].set_ydata(z)
                linew4[0].set_ydata(w)
                      
        if (time.time()-old) > 0.1:
           
            fig.canvas.draw()                             ####เเสดงกราฟ
            fig.canvas.flush_events()
            fig3.canvas.draw()                             ####เเสดงกราฟ
            fig3.canvas.flush_events()
            fig2.canvas.draw()
            fig2.canvas.flush_events()
            old = time.time()
        
    o.close()                                #### ปิด notepad 

