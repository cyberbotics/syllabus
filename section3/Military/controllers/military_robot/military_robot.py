"""military_robot controller."""

# You may need to import some classes of the controller module. Ex:
#  from controller import Robot, Motor, DistanceSensor
from controller import Supervisor

# create the Robot instance.
robot = Supervisor()

# get the time step of the current world.
timestep = int(robot.getBasicTimeStep())


node = robot.getFromDef("ROBOT")

field1 = node.getFieldByIndex(0);
print(field1.getName())
field2 = node.getFieldByIndex(2);
print(field2.getName())
field3 = node.getFieldByIndex(1);
print(field3.getName())
field4 = node.getFieldByIndex(4);
print(field4.getName())
field5 = node.getFieldByIndex(3);
print(field5.getName())

while robot.step(timestep) != -1:
    # Read the sensors:
    # Enter here functions to read sensor data, like:
    #  val = ds.getValue()

    # Process sensor data here.

    # Enter here functions to send actuator commands, like:
    #  motor.setPosition(10.0)
    pass


