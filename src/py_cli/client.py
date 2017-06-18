#!/usr/bin/python           # This is client.py file
import socket               # Import socket module
import os
from bitarray import bitarray
from ctypes import *

def commandloop(command):
	if (command == "OPEN GOOGLE"):
		os.system('open https://google.com')
	elif (command == "SEND EMAIL"):
		os.system('open https://gmail.com')
	elif (command == "SHOW ME TEMPS" | command == "SHOW ME TEMPERATURES")
		os.system('osx-cpu-temp')
	elif (command == "OPEN GOOGLE MUSIC" | "OPEN MUSIC PLAYER"):
		os.system('open https://music.google.com')





def connect(HOST, PORT):
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
	# print(int(size))
	buf = ''
	data = s.recv(1024)
	print data
	s.close
	commandloop(data)

if __name__ == "__main__":
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
	connect(HOST, PORT)
	try:
		os.remove("recording.wav")
	except OSError:
		pass
