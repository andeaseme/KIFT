#!/usr/bin/python           # This is client.py file
import socket               # Import socket module
import os
from bitarray import bitarray



HOST = "127.0.0.1"		  # The remote host
PORT = 22005# The same port as used by the server
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
# sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# server_address = ("127.0.0.1, 10000)
# sock.connect(server_address)
# # call(["rec", "-c 1 -r 16000 -b 16 recording.wav gain +5 silence 1 0.1 3% 1 2.0 3%"])
os.system("rec -c 1 -r 16000 -b 16 recording.wav gain +5 silence 1 0.1 3% 1 2.0 3%")
i = long(os.path.getsize("recording.wav"));
print i;
# print str(bin(i))
s.send(i)
# s.send("recording.wav")
# with open('recording.wav', 'rb') as f:
#   for l in f: s.sendall(l)
f =  open('recording.wav', 'rb')
temp = f.read(i)
s.send(temp)
size = s.recv(4)
size = int(size)
print size
ret = s.recv(size)
# print s.recv(1024)
s.close
