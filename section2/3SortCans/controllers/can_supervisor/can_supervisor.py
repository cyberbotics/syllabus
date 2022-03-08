"""can_supervisor controller."""

# You may need to import some classes of the controller module. Ex:
#  from controller import Robot, Motor, DistanceSensor
import random

from controller import Supervisor

# create the Robot instance.
supervisor = Supervisor()

# get the time step of the current world.
timestep = int(supervisor.getBasicTimeStep())

colors = [[0.937255, 0.160784, 0.160784], [ 0.160784, 0.937255, 0.160784], [0.160784, 0.160784, 0.937255]]

cans_colors = [0, 1, 2, -1, -1, -1, -1]
wrong_can = set()

# for i in range(3, 7):
#     can = 'CAN' + str(i)
#     appearance = can + '_APPEARANCE'
#
#     canNode = supervisor.getFromDef(can)
#     appearanceNode = supervisor.getFromDef(appearance)
#
#     positionField = canNode.getField('translation')
#     colorField = appearanceNode.getField('baseColor')
#     positionField.setSFVec3f([6.96, -0.83, 0.66])
#     randomColor = random.randint(0,2)
#     colorField.setSFColor(color[randomColor])
#     cans_colors[i] = randomColor
#     canNode.resetPhysics()
#     supervisor.step(9000)
i = 3
time = 800
while supervisor.step(timestep) != -1:
    time += 1
    if time % 1100 == 0 and i < 7:
        can = 'CAN' + str(i)
        appearance = can + '_APPEARANCE'

        canNode = supervisor.getFromDef(can)
        appearanceNode = supervisor.getFromDef(appearance)

        positionField = canNode.getField('translation')
        colorField = appearanceNode.getField('baseColor')
        positionField.setSFVec3f([6.96, -0.83, 0.66])
        randomColor = random.randint(0,2)
        colorField.setSFColor(colors[randomColor])
        cans_colors[i] = randomColor
        canNode.resetPhysics()
        i += 1

    success = True

    for j in range(0, 7):
        failure = False
        color = cans_colors[j]
        if color == 0:
            color = 'red'
        elif color == 1:
            color = 'green'
        else:
            color = 'blue'
        can_def = 'CAN' + str(j)
        can = supervisor.getFromDef(can_def)
        position = can.getPosition()
        if can_def not in wrong_can and position[1] > 0.23 and position[1] < 0.66 and position[2] < 0.6: # good y
            if color == 'red':
                if position [0] > -0.15 and position[0] < 0.34: # green box
                    failure = 'green'
                elif position[0] > 0.37 and position [0] < 0.86: # in the blue box
                    failure = 'blue'
                elif not(position[0] > -0.67 and position[0] < -0.18): # not in the red box
                    success = False
            elif color == 'green':
                if position[0] > 0.37 and position [0] < 0.86: # in the blue box
                    failure = 'blue'
                elif position[0] > -0.67 and position[0] < -0.18: # in the red box
                    failure = 'red'
                elif not(position[0] > -0.15 and position[0] < 0.34): # in the green box
                    success = False
            elif color == 'blue':
                if position [0] > -0.15 and position[0] < 0.34: # green box
                    failure = 'green'
                elif position[0] > -0.67 and position[0] < -0.18: # in the red box
                    failure = 'red'
                elif not(position[0] > 0.37 and position [0] < 0.86): # in the blue box
                    success = False
        else:
            success = False
        if failure:
            wrong_can.add(can_def)
            print("Failure: a " + color + " can was added in the " + failure + " box.")
    if success:
        print("SUCCESS")
        break
