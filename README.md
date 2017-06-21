# Knight Industries Forty Two
Project inspired by [KITT](https://en.wikipedia.org/wiki/KITT) from Knight Rider

## Description
Simple voice user interface software using [CMU Sphinx](http://cmusphinx.sourceforge.net/) speech recognition library. 

Additional information available in [KIFT/resources/KIFT.pdf](https://github.com/andeaseme/KIFT/blob/master/resources/KIFT.pdf)

Tested on OS X 10.11

### Server
Handles all speech-to-text functionality, then saves command and audio history if the command is recognized by the client.
### Client
Sends the audio file to the server.  Receives the text.  Processes commands implemented in the client.

## Usage
### Compile and Run
```bash
make
./server
./client #seperate terminal
```
### User Input
For each command, run client
```bash
./client
```
Then speak your command from the list below into your microphone.
### Options
Default server address and port are 127.0.0.1 and 22005.  Both can be modified.
```bash
./server [port_number]
```
```bash
./client [server_address [port_number]]
```

## Voice Command List
Set Egg Timer\
Show Me Temps\
Show Me Temperatures\
Open Google\
Open Google Music\
Open Music Player\
Send E-mail\
Show Me System Information (c) / System Information (python)\
Show Me Weather\
Who Am I\
Show Connected User\
Where Am I\
Lights\
Show History


#### Future updates: fix c client to work with diff ip
