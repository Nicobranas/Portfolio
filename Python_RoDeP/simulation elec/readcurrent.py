import numpy as np
from numpy import empty
import matplotlib.pyplot as plt
import array as arr
import os
from datetime import datetime
from serial import Serial
import time

samp_time=0.01                          #sampling time

date="mesures/"+str(datetime.now())+".txt"
fichier=open(date,"w")                     #.txt copy of the arduino monitor

port="/dev/ttyACM0"
#establishing a serial link with the Arduino board, at 115200 bauds
link = Serial(port, 115200)
#waiting for the connexion to be established
time.sleep(2.0)



while(1):
    time.sleep(samp_time)
    #if (link.available()): 
    fichier.write(link.readline().decode('ascii'))
#res=send_command("?")

link.close()

fichier.close()
