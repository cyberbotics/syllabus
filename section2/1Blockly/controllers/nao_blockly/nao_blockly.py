"""supervisor_blockly controller."""

# You may need to import some classes of the controller module. Ex:
#  from controller import Robot, Motor, DistanceSensor
from controller import Robot, Motion
import struct

# create the Robot instance.
robot = Robot()

# get the time step of the current world.
timestep = int(robot.getBasicTimeStep())

emitter = robot.getDevice("emitter")
receiver = robot.getDevice("receiver")
receiver.enable(timestep)

currentlyPlaying = None

# load motion files
handWave = Motion('../../motions/HandWave.motion')
forwards = Motion('../../motions/Forwards50.motion')
backwards = Motion('../../motions/Backwards.motion')
sideStepLeft = Motion('../../motions/SideStepLeft.motion')
sideStepRight = Motion('../../motions/SideStepRight.motion')
turnLeft40 = Motion('../../motions/TurnLeft40.motion')
turnLeft60 = Motion('../../motions/TurnLeft60.motion')
turnRight40 = Motion('../../motions/TurnRight40.motion')
turnRight60 = Motion('../../motions/TurnRight60.motion')
taichi = Motion('../../motions/Taichi.motion')
wipeForehead = Motion('../../motions/WipeForehead.motion')
handWave = Motion('../../motions/HandWave.motion')

RShoulderRoll = robot.getDevice('RShoulderRoll')
RShoulderPitch = robot.getDevice('RShoulderPitch')
LShoulderRoll = robot.getDevice('LShoulderRoll')
LShoulderPitch = robot.getDevice('LShoulderPitch')
LElbowRoll = robot.getDevice('LElbowRoll')
RElbowRoll = robot.getDevice('RElbowRoll')
RElbowYaw = robot.getDevice('RElbowYaw')
LElbowYaw = robot.getDevice('LElbowYaw')
LAnklePitch = robot.getDevice('LAnklePitch')
LAnkleRoll = robot.getDevice('LAnkleRoll')
RAnklePitch = robot.getDevice('RAnklePitch')
RAnkleRoll = robot.getDevice('RAnkleRoll')

def startMotion(motion, currentlyPlaying):
    # interrupt current motion
    if currentlyPlaying:
        currentlyPlaying.stop()

    # start new motion
    motion.play()
    currentlyPlaying = motion

def move_arms(position):
    if position == "move":
        LShoulderRoll.setPosition(0.349)
        RShoulderRoll.setPosition(-0.349)
        RShoulderPitch.setPosition(1.745)
        LShoulderPitch.setPosition(1.745)
        LElbowRoll.setPosition(-1.396)
        RElbowRoll.setPosition(1.396)
        RElbowYaw.setPosition(1.396)
        LElbowYaw.setPosition(-1.396)
        LAnklePitch.setPosition(-0.027)
        LAnkleRoll.setPosition(0)
        RAnklePitch.setPosition(0.027)
        RAnkleRoll.setPosition(0)   
# Main loop:
# - perform simulation steps until Webots is stopping the controller
end = 0
playing = False
while robot.step(timestep) != -1:
    end -= timestep
    while receiver.getQueueLength() > 0:
      message = receiver.getData();
      message = message.decode("utf-8")
      if message == "forward":
          startMotion(forwards, currentlyPlaying)
          end = forwards.getDuration()
          playing = True
          move_arms("move")
      elif message == "backward":
          startMotion(backwards, currentlyPlaying)
          end = backwards.getDuration()
          playing = True
      elif message == "sideStepLeft":
          startMotion(sideStepLeft, currentlyPlaying)
          end = sideStepLeft.getDuration()
          playing = True
      elif message == "sideStepRight":
          startMotion(sideStepRight, currentlyPlaying)
          end = sideStepRight.getDuration()
          playing = True
      elif message == "turnLeft40":
          startMotion(turnLeft40, currentlyPlaying)
          end = turnLeft40.getDuration()
          playing = True
          move_arms("move")
      elif message == "turnLeft60":
          startMotion(turnLeft60, currentlyPlaying)
          end = turnLeft60.getDuration()
          playing = True
          move_arms("move")          
      elif message == "turnRight40":
          startMotion(turnRight40, currentlyPlaying)
          end = turnRight40.getDuration()
          playing = True
          move_arms("move")          
      elif message == "turnRight60":
          startMotion(turnRight60, currentlyPlaying)
          end = turnRight60.getDuration()
          playing = True
          move_arms("move")
      elif message == "taichi":
          startMotion(taichi, currentlyPlaying)
          end = taichi.getDuration()
          playing = True
      elif message == "wipeForehead":
          startMotion(wipeForehead, currentlyPlaying)
          end = wipeForehead.getDuration()
          playing = True
      elif message == "handWave":
          startMotion(handWave, currentlyPlaying)
          end = handWave.getDuration()
          playing = True
 
      receiver.nextPacket();
    
    if end <= 0 and playing:
        playing = False
        data = "finished".encode("utf-8")
        emitter.send(data)
