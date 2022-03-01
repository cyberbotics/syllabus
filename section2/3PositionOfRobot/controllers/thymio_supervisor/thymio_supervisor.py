"""thymio_supervisor controller."""

from controller import Supervisor
import math

supervisor = Supervisor()

timestep = int(supervisor.getBasicTimeStep())
starting_position = [-1.92164, -2.88506, 0]

thymio = supervisor.getFromDef('THYMIO')

thymio.enableContactPointsTracking(timestep)

while supervisor.step(timestep) != -1:
    contactPoints = thymio.getContactPoints()
    for contactPoint in contactPoints:
        if contactPoint.point[2] > 0.001:
            print("FAIL: an object was hit")
            break
    position = thymio.getPosition()
    x_diff = position[0] - starting_position[0]
    y_diff = position[1] - starting_position[1]
    distance = math.sqrt((x_diff * x_diff) + (y_diff * y_diff))
    
    if distance > 1.8:
        print("SUCCESS")
        break
