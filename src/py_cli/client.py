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
	elif (command == "SHOW ME TEMPS" or command == "SHOW ME TEMPERATURES"):
		os.system('../../osx-cpu-temp/osx-cpu-temp')
	elif (command == "OPEN GOOGLE MUSIC" or command == "OPEN MUSIC PLAYER"):
		os.system('open https://music.google.com')
	elif (command == "SHOW ME WEATHER"):
		os.system('sh weather.sh')
	elif (command == "SYSTEM INFORMATION"):
		os.system('../../neofetch/neofetch')
	elif (command == "SET EGG TIMER"):
		os.system('open https://www.google.com/search?q=8+minute+timer&oq=8+minute+timer&aqs=chrome..69i57j0l5.2158j0j9&sourceid=chrome&ie=UTF-8')
	elif (command == "WHO AM I"): #NEED TO GET MODEL TO RECOGNIZE IT
		os.system('whoami')
	elif (command == 'WHERE AM I'): #NEED TO FIX MODEL
		os.system('hostname')
	else:
		os.system('play ./../../resources/cantdo.wav')

def connect(HOST, PORT):
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.connect((HOST, PORT))
	os.system("rec -c 1 -r 16000 -b 16 recording.wav \
		gain +5 silence 1 0.1 3% 1 2.0 3%")
	i = long(os.path.getsize("recording.wav"));
	print i;
	test = c_long(i)
	s.send(bytearray(test))
	f =  open('recording.wav', 'rb')
	temp = f.read(i)
	s.send(temp)
	size = s.recv(4)
	data = s.recv(1024)
	print data
	s.close
	commandloop(data)

if __name__ == "__main__":
	HOST = "127.0.0.1"
	PORT = 22005
	HOST = raw_input("Enter IP Default (127.0.0.1) if left empty")
	cont = 1
	if HOST is "":
		HOST = "127.0.0.1"
	ans = raw_input("Enter PORT Default (22005) if left empty")
	if ans is "":
		PORT = 22005
	else:
		PORT = int(ans)
	print "HOST:" + HOST
	print "PORT:" + str(PORT)
	while cont:
		connect(HOST, PORT)
		try:
			os.remove("recording.wav")
		except OSError:
			pass
		cont = raw_input("continue?")
		cont = int(cont)
