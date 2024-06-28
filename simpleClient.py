#!/usr/bin/python3

### A simple TCP client ###

from time import *
from socket import *

serverName = "127.0.0.1"
serverPort = 65534
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))
print(clientSocket.getsockname())
sentence = input("Input lowercase sentence:")
clientSocket.send(bytes(sentence, "utf-8"))
modifiedSentence = clientSocket.recv(1024)
print("From Server:", str(modifiedSentence, "utf-8"))
clientSocket.close()
