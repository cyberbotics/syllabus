"""ure_can_grasper_python controller."""
#################### IMPORTS AND INITIALISATION ###########################

# You may need to import some classes of the controller module. Ex:
#  from controller import Robot, Motor, DistanceSensor
from controller import Robot, Motor, DistanceSensor, PositionSensor, Camera
from enum import Enum
import random


class State(Enum):
    WAITING = 1
    GRASPING = 2
    ROTATING = 3
    RELEASING = 4
    ROTATING_BACK = 5


# create the Robot instance.
robot = Robot()


# get the time step of the current world.
TIME_STEP = 32

counter = 0
state = State.WAITING
TARGET_POSITIONS = [-1.88, -2.14, -2.38, -1.51]
SPEED = 1.0


hand_motors = [None] * 3
hand_motors[0] = robot.getDevice('finger_1_joint_1')
hand_motors[1] = robot.getDevice('finger_2_joint_1')
hand_motors[2] = robot.getDevice('finger_middle_joint_1')

ur_motors = [None] * 4
ur_motors[0] = robot.getDevice('shoulder_lift_joint')
ur_motors[1] = robot.getDevice('elbow_joint')
ur_motors[2] = robot.getDevice('wrist_1_joint')
ur_motors[3] = robot.getDevice('wrist_2_joint')

for motor in ur_motors:
    motor.setVelocity(SPEED)

shoulder_rotation = robot.getDevice('shoulder_pan_joint')

shoulder_rotation.setPosition(1.5)

counter = 8

distance_sensor = robot.getDevice('distance sensor')
distance_sensor.enable(TIME_STEP)

position_sensor = robot.getDevice('wrist_1_joint_sensor')
position_sensor.enable(TIME_STEP)

#################### INITIALISE THE CAMERA HERE ##################

########### CREATE 1St FUNCTION HERE #############################


def get_colour_of_can():
    pass

########### CREATE 2ND FUNCTION HERE ##############################


def rotate_robotic_shoulder():
    pass

#################### MAINS LOOP ############################################


# - perform simulation steps until Webots stops the controller
while robot.step(TIME_STEP) != -1:
    if counter <= 0:
        if state == state.WAITING:
            if distance_sensor.getValue() < 500:
                state = state.GRASPING
                counter = 8
                for motor in hand_motors:
                    motor.setPosition(0.85)

                ######## GET THE COLOUR OF THE CAN HERE ############
                colour = get_colour_of_can()
                ####################################################
        elif state == state.GRASPING:
            i = 0
            for motor in ur_motors:
                motor.setPosition(TARGET_POSITIONS[i])
                i += 1
            ######### MOVE THE ARM HERE ##############
            rotate_robotic_shoulder()
            ##########################################
            state = state.ROTATING
        elif state == state.ROTATING:
            if position_sensor.getValue() < -2.3:
                counter = 8
                state = state.RELEASING
                for motor in hand_motors:
                    motor.setPosition(motor.getMinPosition())
        elif state == state.RELEASING:
            for motor in ur_motors:
                motor.setPosition(0.0)
            state = state.ROTATING_BACK
        elif state == state.ROTATING_BACK:
            ####### PUT THE ARM BACK IN POSITION HERE ##############

            ########################################################
            if position_sensor.getValue() > -0.1:
                state = state.WAITING
    counter -= 1
