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

for i in range(4):
    can = 'CAN' + str(i)
    appearance = can + '_APPEARANCE'

    canNode = supervisor.getFromDef(can)
    appearanceNode = supervisor.getFromDef(appearance)

    positionField = canNode.getField('translation')
    colorField = appearanceNode.getField('baseColor')
    positionField.setSFVec3f([6.96, -0.83, 0.66])
    colorField.setSFColor(color[random.randint(0,2)])
    canNode.resetPhysics()
    supervisor.step(9000)
