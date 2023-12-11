import serial
import struct
import re
import math
import time
import matplotlib.pyplot as plt
import numpy as np
#fig3, cx = plt.subplots()

#cx.axis([0, 50, -20, 20])
w = [0]*50
G = [0]*50

#lineG = cx.plot(G, label='Average')

#cx.legend()


#fig3.canvas.manager.show()
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
    while True:
        msg = ser.readline()
        if len(msg)>0:
            mD = str(msg)
            m = mD.split('\\t')
            
            if len(m)==3:
               
                f = float(m[1]) #ตัวที่ 2
                #p = m[0]
                #k = (p[2:]) #ตัวที่ 1 k
                k = m[0].strip("b'")

                try:
                    u = float(k)
                except ValueError:
                    continue
                a = m[2]
                try:
                    c = float(a.strip('\\r\\n\''))###ตัวที่ 3
                except ValueError:
                    continue
                h = math.sqrt((u)**2+float(f)**2+(c)**2)   ####  ผลรวม
                G1 = (h+(w[49])*10)/11
                if h > 10:
                    print(msg)
                w.append(h)
                G.append(G1)
                w.remove(w[0])
                G.remove(G[0])
                print(u,f,c,h)
              #  lineG[0].set_ydata(G)               # ใส่ตัวเเปร x ใน เส้น x
           
       #     if (time.time()-old) > 0.1:
           
              #  fig3.canvas.draw()                             ####เเสดงกราฟ
               # fig3.canvas.flush_events()
   
                #old = time.time()


