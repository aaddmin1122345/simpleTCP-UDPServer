#!/usr/bin/python3

### A simple TCP server ###

from socket import *

serverPort = 65534
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(("", serverPort))
serverSocket.listen(0)
print(serverSocket.getsockname())
print("服务器已准备好接受")
while 1:
    connectionSocket, addr = serverSocket.accept()
    print(connectionSocket.getsockname())
    sentence = connectionSocket.recv(1024)
    capitalizedSentence = sentence.upper()
    connectionSocket.send(capitalizedSentence)
    connectionSocket.close()
