# Copyright 1996-2022 Cyberbotics Ltd.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""
Default controller of the iRobot Create robot
"""

from controller import Robot
import random


class Create(Robot):
    def __init__(self):
        super(Create, self).__init__()
        self.timeStep = int(self.getBasicTimeStep())
        self.receiver = self.getDevice('receiver')
        self.receiver.enable(self.timeStep)
        self.led_on = self.getDevice('led_on')
        self.led_play = self.getDevice('led_play')
        self.led_step = self.getDevice('led_step')
        self.bumper_left = self.getDevice('bumper_left')
        self.bumper_right = self.getDevice('bumper_right')
        self.bumpers = [self.bumper_left, self.bumper_right]
        for bumper in self.bumpers:
            bumper.enable(self.timeStep)
        self.cliff_left = self.getDevice('cliff_left')
        self.cliff_right = self.getDevice('cliff_right')
        self.cliff_front_left = self.getDevice('cliff_front_left')
        self.cliff_front_right = self.getDevice('cliff_front_right')
        self.cliffs = [self.cliff_left, self.cliff_right, self.cliff_front_left, self.cliff_front_right]
        for cliff in self.cliffs:
            cliff.enable(self.timeStep)
        self.left_motor = self.getDevice('left wheel motor')
        self.right_motor = self.getDevice('right wheel motor')
        self.motors = [self.left_motor, self.right_motor]
        for motor in self.motors:
            motor.setPosition(float("inf"))
            motor.setVelocity(0)

        self.left_position_sensor = self.getDevice('left wheel sensor')
        self.right_position_sensor = self.getDevice('right wheel sensor')
        self.position_sensors = [self.left_position_sensor, self.right_position_sensor]
        for position_sensor in self.position_sensors:
            position_sensor.enable(self.timeStep)

    def flush_ir_receiver(self):
        while self.receiver.getQueueLength() > 0:
            self.receiver.nextPacket()

    def virtual_wall(self):
        return self.receiver.getQueueLength() > 0

    def collision_at_left(self):
        return self.bumper_left.getValue() != 0

    def collision_at_right(self):
        return self.bumper_right.getValue() != 0

    def cliff_at_left(self):
        return self.cliff_left.getValue() < 100 or self.cliff_front_left.getValue() < 100

    def cliff_at_right(self):
        return self.cliff_right.getValue() < 100 or self.cliff_front_right.getValue() < 100

    def cliff_at_front(self):
        return self.cliff_front_left.getValue() < 100 or self.cliff_front_right.getValue() < 100

    def go_forward(self):
        self.left_motor.setVelocity(16)
        self.right_motor.setVelocity(16)

    def go_backward(self):
        self.left_motor.setVelocity(-8)
        self.right_motor.setVelocity(-8)

    def stop(self):
        self.left_motor.setVelocity(0)
        self.right_motor.setVelocity(0)

    def turn(self, angle):
        angle = angle * 3.1415927 / 180  # convert from degree to radian
        WHEEL_RADIUS = 0.031
        AXLE_LENGTH = 0.271756
        self.stop()
        l_offset = self.left_position_sensor.getValue()
        r_offset = self.right_position_sensor.getValue()
        if self.step(self.timeStep) == -1:
            return
        neg = -1 if angle < 0 else 1
        self.left_motor.setVelocity(neg * 8)
        self.right_motor.setVelocity(-neg * 8)
        while True:
            left = self.left_position_sensor.getValue() - l_offset
            right = self.right_position_sensor.getValue() - r_offset
            dl = left * WHEEL_RADIUS  # distance covered by left wheel in meter
            dr = right * WHEEL_RADIUS  # distance covered by right wheel in meter
            orientation = neg * (dl - dr) / AXLE_LENGTH  # delta orientation in radian
            if self.step(self.timeStep) == -1:
                return
            if orientation >= neg * angle:
                break
        self.stop()
        self.step(self.timeStep)

    def wait(self, seconds):
        startTime = self.getTime()
        while self.step(self.timeStep) != -1:
            if startTime + seconds <= self.getTime():
                break

    def run(self):
        self.led_on.set(True)
        self.wait(0.5)
        while self.step(self.timeStep) != -1:
            if self.virtual_wall():
                print('Virtual wall detected')
                self.turn(180)
            elif self.collision_at_left() or self.cliff_at_left():
                print('Left obstacle detected')
                self.go_backward()
                self.wait(0.5)
                self.turn(random.uniform(0, 180))
            elif self.collision_at_right() or self.cliff_at_right() or self.cliff_at_front():
                print('Right obstacle detected')
                self.go_backward()
                self.wait(0.5)
                self.turn(random.uniform(-180, 0))
            else:
                self.go_forward()
            self.flush_ir_receiver()


controller = Create()
controller.run()
