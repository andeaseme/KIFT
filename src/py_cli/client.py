#!/usr/bin/python           # This is client.py file
import socket               # Import socket module
from subprocess import call


# def functionname( parameters ):



s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#host = socket.gethostname()
port = 22005
print ("HERE")
s.connect(('127.0.0.1', port))
call(["rec", "-c 1 -r 16000 -b 16 recording.wav gain +5 silence 1 0.1 3% 1 2.0 3%"])

# print s.recv(1024)
s.close
