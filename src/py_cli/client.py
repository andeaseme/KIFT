#!/usr/bin/python           # This is client.py file
import socket               # Import socket module
import os
from bitarray import bitarray
from ctypes import *

HOST = "127.0.0.1"
PORT = 22005

HOST = raw_input("Enter IP Default (127.0.0.1) if left empty")
if HOST is "":
	HOST = "127.0.0.1"
ans = raw_input("Enter PORT Default (22005) if left empty")
if ans is "":
	PORT = 22005
else:
	PORT = int(ans)

print "HOST:" + HOST
print "PORT:" + str(PORT)

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
os.system("rec -c 1 -r 16000 -b 16 recording.wav gain +5 silence 1 0.1 3% 1 2.0 3%")
i = long(os.path.getsize("recording.wav"));
print i;
test = c_long(i)
s.send(bytearray(test))
f =  open('recording.wav', 'rb')
temp = f.read(i)
s.send(temp)
size = s.recv(4)
buf = ''
data = s.recv(1024)
print data
s.close
