"""can_supervisor controller."""

from controller import Supervisor

supervisor = Supervisor()

timestep = int(supervisor.getBasicTimeStep())

can = supervisor.getFromDef('CAN')

while supervisor.step(timestep) != -1:
    position = can.getPosition()
    if position[0] > -0.09 and position[0] < 0.51:
        if position[1] > 0.26 and position[1] < 0.71:
            if position[2] > 0 and position[2] < 0.4:
                print("SUCCESS")
                break
    
