from controller import Robot
import sys
import optparse
try:
    import numpy as np
except ImportError:
    sys.exit("Warning: 'numpy' module not found.")

class Mavic (Robot):
    # Constants, empirically found.
    K_VERTICAL_THRUST = 68.5  # with this thrust, the drone lifts.
    # Vertical offset where the robot actually targets to stabilize itself.
    K_VERTICAL_OFFSET = 0.6
    K_VERTICAL_P = 3.0        # P constant of the vertical PID.
    K_ROLL_P = 50.0           # P constant of the roll PID.
    K_PITCH_P = 30.0          # P constant of the pitch PID.

    MAX_YAW_DISTURBANCE = 0.4
    MAX_PITCH_DISTURBANCE = -1
    # Precision between the target position and the robot position in meters
    target_precision = 0.5

    def __init__(self):
        Robot.__init__(self)

        self.time_step = int(self.getBasicTimeStep())

        # Get and enable devices.
        self.camera = self.getDevice("camera")
        self.camera.enable(self.time_step)
        self.imu = self.getDevice("inertial unit")
        self.imu.enable(self.time_step)
        self.gps = self.getDevice("gps")
        self.gps.enable(self.time_step)
        self.gyro = self.getDevice("gyro")
        self.gyro.enable(self.time_step)

        self.front_left_motor = self.getDevice("front left propeller")
        self.front_right_motor = self.getDevice("front right propeller")
        self.rear_left_motor = self.getDevice("rear left propeller")
        self.rear_right_motor = self.getDevice("rear right propeller")
        self.camera_pitch_motor = self.getDevice("camera pitch")
        self.camera_pitch_motor.setPosition(1.55)  # vertical PoV
        motors = [self.front_left_motor, self.front_right_motor,
                  self.rear_left_motor, self.rear_right_motor]
        for motor in motors:
            motor.setPosition(float('inf'))
            motor.setVelocity(0)

        self.current_pose = 6*[0]  # X,Y,Z, yaw, pitch, roll
        self.target_position = [0, 0, 0]
        self.target_index = 0
        self.target_altitude = 0

    def run(self):
        while self.step(self.time_step) != -1:
            pass

robot = Mavic()
robot.run()
