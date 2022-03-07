"""can_supervisor controller."""

# You may need to import some classes of the controller module. Ex:
#  from controller import Robot, Motor, DistanceSensor
import random

from controller import Supervisor

# create the Robot instance.
supervisor = Supervisor()

# get the time step of the current world.
timestep = int(supervisor.getBasicTimeStep())

supervisor.step(3500)
color = [[0.937255, 0.160784, 0.160784], [ 0.160784, 0.937255, 0.160784], [0.160784, 0.160784, 0.937255]]

cans_colors = [0, 1, 2, -1, -1, -1, -1]

for i in range(3, 7):
    can = 'CAN' + str(i)
    appearance = can + '_APPEARANCE'

    canNode = supervisor.getFromDef(can)
    appearanceNode = supervisor.getFromDef(appearance)

    positionField = canNode.getField('translation')
    colorField = appearanceNode.getField('baseColor')
    positionField.setSFVec3f([6.96, -0.83, 0.66])
    randomColor = random.randint(0,2)
    colorField.setSFColor(color[randomColor])
    cans_colors[i] = randomColor
    canNode.resetPhysics()
    supervisor.step(9000)

while supervisor.step(timestep) != -1:
    success = True
    failure = False

    for i in range(0, 7):
        color = cans_colors[i]
        can_def = 'CAN' + str(i)
        can = supervisor.getFromDef(can_def)
        position = can.getPosition()
        if position[1] > 0.23 and position[1] < 0.66 and position[2] < 0.6: # good y
            if color == 0: # red
                if position [0] > -0.15 and position [0] < 0.86: # in the blue or green box
                    failure = True
                elif not(position[0] > -0.67 and position[0] < -0.18): # not in the red box
                    success = False
            elif color == 1: # green
                if position[0] > 0.37 and position [0] < 0.86: # in the blue box
                    failure = True
                elif position[0] > -0.67 and position[0] < -0.18: # in the red box
                    failure = True
                elif not(position[0] > -0.15 and position[0] < 0.34): # in the green box
                    success = False
            elif color == 2: # blue
                if position[0] > -0.67 and position[0] < 0.34: # in the red or green box
                    failure = True
                elif not(position[0] > 0.37 and position [0] < 0.86): # in the blue box
                    success = False
        else:
            success = False
    if failure:
        print("FAILURE: a can was put in the wrong box")
        break
    elif success:
        print("SUCCESS")
        break
