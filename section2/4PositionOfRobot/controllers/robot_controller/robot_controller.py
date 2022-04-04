"""Braitenberg-based obstacle-avoiding robot controller."""
#################### IMPORTS AND INITIALISATION ###########################

from controller import Robot

# Get reference to the robot.
robot = Robot()

# Get simulation step length.
TIME_STEP = int(robot.getBasicTimeStep())

# Constants of the Thymio II motors and distance sensors.
MAX_MOTOR_VELOCITY = 9.53
DIST_SENSOR_CAL_CONST = 360

# Get left and right wheel motors.
lhs_motor = robot.getDevice('motor.left')
rhs_motor = robot.getDevice('motor.right')

# Get frontal distance sensors.
lhs_sensor = robot.getDevice('prox.horizontal.0')
mid_lhs_sensor = robot.getDevice('prox.horizontal.1')
mid_sensor = robot.getDevice('prox.horizontal.2')
mid_rhs_sensor = robot.getDevice('prox.horizontal.3')
rhs_sensor = robot.getDevice('prox.horizontal.4')

# Enable distance sensors.
lhs_sensor.enable(TIME_STEP)
mid_lhs_sensor.enable(TIME_STEP)
mid_sensor.enable(TIME_STEP)
mid_rhs_sensor.enable(TIME_STEP)
rhs_sensor.enable(TIME_STEP)

#################### WRITE YOUR CODE HERE ###########################
