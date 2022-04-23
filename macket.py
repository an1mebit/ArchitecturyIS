from udpServer import server
from udpClient import client
import threading

class Pulivizer:
    def __init__(self):
        pass
    class onAndOffPulivizer:
        def __init__(self):
            pass
        def on():
            pass
        def off():
            pass

class Camera:
    def __init__(self):
        pass
    def uses(self):
        self.determenant = GraffityDetermenant()
    def getCoordinate(self):
        pass

class ControlSystem:
    def __init__(self):
        pass
    def onAndOfRobot(self, state):
        pass
    def commandReciver(self, string):
        self.string = string
    def go(self, angle, speed):
        cam = Camera()
        coordinate = Camera.getCoordinate(self)
        self.angle = angle
        self.speed = speed
    def stop(self, angle):
        self.angle = angle

class GraffityDetermenant:
    def __init__(self):
        pass


def checkStatus(status):
    robot = Robot()
    if(status == '1'):
        print('[INFO] I get motivation')
        robot.control.onAndOfRobot(True)
    elif(status == '2'):
        print('[INFO] Determination of graffity')
        robot.cam.uses()
        print('[INFO] Getting coordinate of destination')
        robot.cam.getCoordinate()
    elif(status == '3'):
        print('[INFO] Go to destination')
        robot.control.go(90, 100)
    elif(status == '4'):
        print('[INFO] Stop')
        robot.control.stop(0)
    elif(status == '5'):
        print('[INFO] Start shading')
        robot.puliviz.onAndOffPulivizer.on()
    elif(status == '6'):
        print('[INFO] Stop shading')
        robot.puliviz.onAndOffPulivizer.off()
    elif(status == '7'):
        print('[INFO] Change the world, my finall message, goodbye')
        robot.control.onAndOfRobot(False)
    elif(status == 'exit'):
        exit('[SYS] Success')
    else:
        print('[ERR] Something goes wrong')

class Robot:
    def __init__(state=False):
        pass
    puliviz = Pulivizer()
    control = ControlSystem()
    cam = Camera()
    
    class EventHandler:
        def __init__(self, func=None):
            if func:
                self.Event = func
        def Event(self):
            pass

def EventTerminal():
    while True:
        status = input()
        checkStatus(status)

def EventNet():
    while True:
        msg = input()
        client(msg)

def main():
    print('[SYS] Choose:/')
    while True:
        rob = Robot()
        command = input()
        if command == 'term':
            print('[SYS] Enter the command: ')
            event = rob.EventHandler(EventTerminal)
            event.Event()
        elif command == 'net':
            print('[SYS] Net starting... ')
            event = rob.EventHandler(EventNet)
            thread = threading.Thread(target=server)
            thread.start()
            event.Event()
            thread.join()
            print('[SYS] Net end')
        elif command == 'exit':
            exit('[SYS] Success')
        else:
            print('[SYS] Please, enter correct command')
    

if __name__ == '__main__':
    main()