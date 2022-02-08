from controller import Robot, Motion


class Sprinter(Robot):
    """Make the NAO robot run as fast as possible."""

    def initialize(self):
        """Get device pointers, enable sensors and set robot initial pose."""
        # This is the time step (ms) used in the motion file.
        self.timeStep = 40
        # Get pointers to the shoulder motors.
        self.RShoulderPitch = self.getDevice('RShoulderPitch')
        self.LShoulderPitch = self.getDevice('LShoulderPitch')
        # Move the arms down.
        self.RShoulderPitch.setPosition(1.1)
        self.LShoulderPitch.setPosition(1.1)

    def run(self):
        """Play the forward motion and loop on the walking cycle."""
        walk = Motion('forward.motion')
        walk.setLoop(True)
        walk.play()
        while True:

            if walk.getTime() == 1360:  # we reached the end of forward.motion
                # loop back to the beginning of the walking sequence
                walk.setTime(360)
            # Perform a simulation step, quit if the simulation is over.
            if self.step(self.timeStep) == -1 or self.getCustomData() == "stop":
                break


controller = Sprinter()
controller.initialize()
controller.run()
