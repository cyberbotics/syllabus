"""thymio_supervisor controller."""

from controller import Supervisor
import math

supervisor = Supervisor()

timestep = int(supervisor.getBasicTimeStep())
starting_position = [-1.92164, -2.88506, 0]

floor = supervisor.getFromDef("FLOOR")
floor_id = floor.getId()
thymio = supervisor.getFromDef("THYMIO")

thymio.enableContactPointsTracking(timestep, True)

while supervisor.step(timestep) != -1:
    contactPoints = thymio.getContactPoints(True)
    for contactPoint in contactPoints:
        if contactPoint.node_id != floor_id:
            print("FAIL: an object was hit")
            break
    position = thymio.getPosition()
    x_diff = position[0] - starting_position[0]
    y_diff = position[1] - starting_position[1]
    distance = math.sqrt((x_diff * x_diff) + (y_diff * y_diff))
    
    if distance > 2:
        print("SUCCESS")
        break
