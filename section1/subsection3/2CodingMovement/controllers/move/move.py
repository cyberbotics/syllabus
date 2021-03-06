"""Simple robot controller."""

from controller import Robot
import sys

# Define the target motor position in radians.
target = 40

# Get pointer to the robot.
robot = Robot()

# Print the program output on the console
print("Move the motors of the Thymio II to position " + str(target) + ".")
sys.stderr.write("This is a sample error message.\n")

# Set the target position of the left and right wheels motors.
robot.getDevice("motor.left").setPosition(target)
robot.getDevice("motor.right").setPosition(target)
i = 0

while robot.step(int(robot.getBasicTimeStep())) != -1:
    i += 1