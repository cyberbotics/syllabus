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
        walk.play()

        while self.step(self.timeStep) != -1:
            pass


controller = Sprinter()
controller.initialize()
controller.run()
