class Robot:
    def __init__(self, state = False):
        pass
    def have(self):
        self.puliviz = Pulivizer()
    def controlled(self):
        self.control = ControllSystem()
    def uses(self):
        self.cam = Camera()

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
    def getCoordinate():
        return

class ControllSystem:
    def __init__(self):
        pass
    def onAndOfRobot(self, state):
        self.robot = Robot(state)
    def commandReciver(self, string):
        self.string = string
    def go(self, angle, speed):
        cam = Camera()
        coordinate = Camera.getCoordinate()
        self.angle = angle
        self.speed = speed
    def stop(self, angle):
        self.angle = angle

class GraffityDetermenant:
    def __init__(self):
        pass

def checkStatus(status):
    robot = Robot()
    if(status == 1):
        print('[INFO] I get motivation')
        robot.control.onAndOfRobot(True)
    elif(status == 2):
        print('[INFO] Determination of graffity')
        robot.cam.determenant()
        print('[INFO] Getting coordinate of destination')
        robot.cam.getCoordinate()
    elif(status == 3):
        print('[INFO] Go to destination')
        robot.control.go()
    elif(status == 4):
        print('[INFO] Stop')
        robot.control.stop()
    elif(status == 5):
        print('[INFO] Start shading')
        robot.puliviz.onAndOffPulivizer.on()
    elif(status == 6):
        print('[INFO] Stop shading')
        robot.puliviz.onAndOffPulivizer.off()
    elif(status == 7):
        print('[INFO] Change the world, my finall message, goodbye')
        robot.control.onAndOfRobot(False)
    else:
        print('[ERR] Something goes wrong')
        exit(-1)