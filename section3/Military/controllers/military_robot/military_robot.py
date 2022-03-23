"""military_robot controller."""

# You may need to import some classes of the controller module. Ex:
#  from controller import Robot, Motor, DistanceSensor
from controller import Robot, Motor

# create the Robot instance.
robot = Robot()

# get the time step of the current world.
timestep = int(robot.getBasicTimeStep())

leftMotor = robot.getDevice('left motor');
rightMotor = robot.getDevice('right motor');

turretMotor = robot.getDevice('turret_motor');
gunsMotor = robot.getDevice('guns_motor');
gunsMotor.setPosition(0.45)

leftMotor.setPosition(float('inf'))
rightMotor.setPosition(float('inf'))

leftMotor.setVelocity(1)
rightMotor.setVelocity(1)

timeStep = robot.getBasicTimeStep();

robot.step(13500)

leftMotor.setVelocity(0.5)

robot.step(4000)

leftMotor.setVelocity(0)
rightMotor.setVelocity(0)
turretMotor.setPosition(0.93)

robot.step(500)
gunsMotor.setPosition(-0.05)