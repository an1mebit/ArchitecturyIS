import socket

def server():
    localIP = "127.0.0.1"
    localPORT = 20001
    bufferSize = 1024

    msgFromServer = "hi client"
    bytesToSend = str.encode(msgFromServer)

    UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

    UDPServerSocket.bind((localIP, localPORT))

    print('[SYS] Server listenning')

    while True:
        bytesAddressPair = UDPServerSocket.recvfrom(bufferSize)

        message = bytesAddressPair[0]
        address = bytesAddressPair[1]

        clientMSG = "Message from client: {}".format(message)
        if clientMSG == "exit":
            exit("[SYS] Success")
        clientIP = "Client IP address: {}".format(address)

        print(clientMSG, clientIP)

        UDPServerSocket.sendto(bytesToSend, address)