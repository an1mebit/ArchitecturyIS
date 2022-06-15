import socket

def client(msgFromClient):

    bytesToSend = str.encode(msgFromClient)
    serverAddressPort = ('127.0.0.1', 20001)
    bufferSize = 1024

    UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

    UDPClientSocket.sendto(bytesToSend, serverAddressPort)

    msgFromServer = UDPClientSocket.recvfrom(bufferSize)

    msg = "[SYS] message from server {}".format(msgFromServer[0])

    print(msg)