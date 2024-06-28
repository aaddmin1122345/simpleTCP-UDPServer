#!/usr/bin/python3

### A simple UDP client ###

from socket import *

serverName = "127.0.0.1"
serverPort = 65533
clientSocket = socket(AF_INET, SOCK_DGRAM)
message = input("输入一个小写字母:")
clientSocket.sendto(bytes(message, "utf-8"), (serverName, serverPort))
modifiedMessage, serverAddress = clientSocket.recvfrom(2048)
print(str(modifiedMessage, "utf-8"))
clientSocket.close()
