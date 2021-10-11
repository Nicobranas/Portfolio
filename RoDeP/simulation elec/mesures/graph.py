import numpy as np
from numpy import empty
import matplotlib.pyplot as plt
import array as arr
import os
import datetime
import argparse

'''parser = argparse.ArgumentParser()
parser.add_argument('--name_file', type=str, nargs=1, default="monitor.txt", help='Need the name file')

filename = parser.parse_args()'''

filename="led en moins"

samp_time=0.01                  #sampling time

file=open(filename+".txt")                 #.txt copy of the arduino monitor

text=file.readlines()                   #count of the number of line
NumberOfLine = len(text)
file.seek(0)

##############              Mangements informations             ###############

#x_time= arr.array('f',(0,)*(NumberOfLine))  #finals tables whithout command
#y_curr = arr.array('f',(0,)*(NumberOfLine))
x_time= arr.array('f',(0,)*(NumberOfLine))
y_curr = arr.array('f',(0,)*(NumberOfLine))
y_smoo = arr.array('f',(0,)*(NumberOfLine))
y_avg = arr.array('f',(0,)*(NumberOfLine))
moy=0
'''for i in range(len(x_time)):
    x_time[i]=samp_time*i'''
for i in range(len(text)):
    x_time[i]=samp_time*i
    y_curr[i]=float(file.readline().rstrip())
    moy=moy+y_curr[i]
    
for i in range(len(text)):
    y_avg[i]=moy/len(text)
    
y_smoo_tem=0
y_smoo[0]=y_curr[0]
for i in range(1,10):
    for y in range(i):
        y_smoo_tem=y_smoo_tem+y_curr[y]
    y_smoo[i]=y_smoo_tem/i
    y_smoo_tem=0
    
for i in range(10,len(text)):
    for y in range(i-10,i):
        y_smoo_tem=y_smoo_tem+y_curr[y]
    y_smoo[i]=y_smoo_tem/10
    y_smoo_tem=0

###############            Create and save a figure              #####################

fig = plt.figure()                      
axes = fig.add_subplot(111)                 
axes.set_xlabel('time (s)')
axes.set_ylabel('Current (A)')
plt.plot(x_time, y_curr)
plt.plot(x_time, y_smoo)
plt.plot(x_time, y_avg)
plt.xlim(0,1)
plt.ylim(0.2,0.4)
plt.legend(['measured current','average of the last 10 measurements','average current = '+str(round(moy/len(text),3))+' A'])
plt.show()                              #print
#title=datetime.datetime.now().strftime("%c")+".png"
fig.savefig(filename+".png")
