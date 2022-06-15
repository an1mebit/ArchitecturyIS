import socket

msgFromClient = input()
bytesToSend = str.encode(msgFromClient)
serverAddressPort = ('10.0.2.2', 1103)
bufferSize = 1024

UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
UDPClientSocket.sendto(bytesToSend, serverAddressPort)

msgFromServer = UDPClientSocket.recvfrom(bufferSize)
msg = "[SYS] message from server {}".format(msgFromServer[0])
print(msg)