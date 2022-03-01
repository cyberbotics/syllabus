"""thymio_supervisor controller."""

# You may need to import some classes of the controller module. Ex:
#  from controller import Robot, Motor, DistanceSensor
from controller import Supervisor
import math

# create the Robot instance.
supervisor = Supervisor()

# get the time step of the current world.
timestep = int(supervisor.getBasicTimeStep())
starting_position = [-1.92164, -2.88506, 0]
thymio = supervisor.getFromDef("THYMIO");

# Main loop:
# - perform simulation steps until Webots is stopping the controller
while supervisor.step(timestep) != -1:
    position = thymio.getPosition()
    x_diff = position[0] - starting_position[0]
    y_diff = position[1] - starting_position[1]
    distance = math.sqrt((x_diff * x_diff) + (y_diff * y_diff))
    
    if distance > 2:
        print("SUCCESS")
        break
