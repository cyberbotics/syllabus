"""Braitenberg-based obstacle-avoiding robot controller."""
#################### IMPORTS AND INITIALIZATION ###########################

from controller import Robot

# Get reference to the robot.
robot = Robot()

# Get simulation step length.
TIME_STEP = int(robot.getBasicTimeStep())

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
outerLeftSensor.enable(TIME_STEP)
centralLeftSensor.enable(TIME_STEP)
centralSensor.enable(TIME_STEP)
centralRightSensor.enable(TIME_STEP)
outerRightSensor.enable(TIME_STEP)

#################### WRITE YOUR CODE HERE ###########################
