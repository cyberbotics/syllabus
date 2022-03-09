"""Braitenberg-based obstacle-avoiding robot controller."""
#################### IMPORTS AND INITIALIZATION ###########################

from controller import Robot

# Get reference to the robot.
robot = Robot()

# Get simulation step length.
timeStep = int(robot.getBasicTimeStep())

# Constants of the Thymio II motors and distance sensors.
maxMotorVelocity = 9.53
distanceSensorCalibrationConstant = 360

# Get left and right wheel motors.
leftMotor = robot.getDevice('motor.left')
rightMotor = robot.getDevice('motor.right')

# Get frontal distance sensors.
outerLeftSensor = robot.getDevice('prox.horizontal.0')
centralLeftSensor = robot.getDevice('prox.horizontal.1')
centralSensor = robot.getDevice('prox.horizontal.2')
centralRightSensor = robot.getDevice('prox.horizontal.3')
outerRightSensor = robot.getDevice('prox.horizontal.4')

# Enable distance sensors.
outerLeftSensor.enable(timeStep)
centralLeftSensor.enable(timeStep)
centralSensor.enable(timeStep)
centralRightSensor.enable(timeStep)
outerRightSensor.enable(timeStep)

#################### WRITE YOUR CODE HERE ###########################
