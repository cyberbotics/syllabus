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

"""Demonstration of inverse kinematics using the "ikpy" Python module."""

import sys
import tempfile
try:
    import ikpy
    from ikpy.chain import Chain
except ImportError:
    sys.exit('The "ikpy" Python module is not installed. '
             'To run this sample, please upgrade "pip" and install ikpy with this command: "pip install ikpy"')

import math
from controller import Supervisor

if ikpy.__version__[0] < '3':
    sys.exit('The "ikpy" Python module version is too old. '
             'Please upgrade "ikpy" Python module to version "3.0" or newer with this command: "pip install --upgrade ikpy"')


IKPY_MAX_ITERATIONS = 4

# Initialize the Webots Supervisor.
supervisor = Supervisor()
timeStep = int(4 * supervisor.getBasicTimeStep())

receiver = supervisor.getDevice("receiver");
receiver.enable(timeStep)

sensors = False
button = False

translations = []
car1 = supervisor.getFromDef("CAR1");
car2 = supervisor.getFromDef("CAR2");
car3 = supervisor.getFromDef("CAR3");
translations.append(car1.getField("translation"));
translations.append(car2.getField("translation"));
translations.append(car3.getField("translation"));

ds0 = supervisor.getDevice('ds0')
ds1 = supervisor.getDevice('ds1')

ds0.enable(timeStep)
ds1.enable(timeStep)
# Create the arm chain from the URDF
filename = None
with tempfile.NamedTemporaryFile(suffix='.urdf', delete=False) as file:
    filename = file.name
    file.write(supervisor.getUrdf().encode('utf-8'))
armChain = Chain.from_urdf_file(filename)
for i in [0, 6]:
    armChain.active_links_mask[i] = False

speed = 5
prevSpeed = 5

# Initialize the arm motors and encoders.
motors = []
position_sensors = []
for link in armChain.links:
    if 'motor' in link.name:
        motor = supervisor.getDevice(link.name)
        motor.setVelocity(speed)
        position_sensor = motor.getPositionSensor()
        position_sensor.enable(timeStep)
        position_sensors.append(position_sensor)
        motors.append(motor)

led = supervisor.getDevice('welding_torch')
on = True

# Get the arm and target nodes.
arm = supervisor.getSelf()

i = 101
while supervisor.step(timeStep) != -1:
    stop = False
    if (sensors and (ds0.getValue() != 0 or ds1.getValue() != 0)) or button:
        stop = True

    for j in range(len(motors)):
        motors[j].setVelocity(speed)
    
    armPosition = arm.getPosition()
    if i > 100: 
        targetPosition = [-3, 2, 1.37]
    else:
        targetPosition = [-0.75, 0.54, 1.93]
    
    # Compute the position of the target relatively to the arm.
    # x and y axis are inverted because the arm is not aligned with the Webots global axes.
    x = targetPosition[0] - armPosition[0]
    y = targetPosition[1] - armPosition[1]
    z = targetPosition[2] - armPosition[2]
    
    # Call "ikpy" to compute the inverse kinematics of the arm.
    initial_position = [0] + [m.getPositionSensor().getValue() for m in motors] + [0]
    ikResults = armChain.inverse_kinematics([x, y, z], max_iter=IKPY_MAX_ITERATIONS, initial_position=initial_position)
    
    # Recalculate the inverse kinematics of the arm if necessary.
    position = armChain.forward_kinematics(ikResults)
    squared_distance = (position[0, 3] - x)**2 + (position[1, 3] - y)**2 + (position[2, 3] - z)**2
    if math.sqrt(squared_distance) > 0.03:
        ikResults = armChain.inverse_kinematics([x, y, z])
    
    if stop:
        for j in range(len(position_sensors)):
            ikResults[j + 1] = position_sensors[j].getValue()
    # Actuate the arm motors with the IK results.
    for j in range(len(motors)):
        motors[j].setPosition(ikResults[j + 1])
        
    if i > 40 and i < 65 and not stop:
        led.set(1)
    if i > 65:
        led.set(0)
    i += 1

    for j in range(0, 3):
        pos = translations[j].getSFVec3f()
        if pos[1] <= -12.5:
          newPos = [0, 17.5, 0.44];
          translations[j].setSFVec3f(newPos);
        elif pos[1] >= 3.8 and pos[1] <=3.9:
          i = 0
    
    while receiver.getQueueLength() > 0:    
        message = receiver.getData().decode("utf-8");
        if message == "sensor":
            sensors = not sensors
        elif message == "button":
            button = not button
            if button:
                led.set(0)
        elif message == "speed":
            if speed == 0:
                prevSpeed = 5 if prevSpeed == 1 else 1
            else:
                speed = 5 if speed == 1 else 1
        receiver.nextPacket()