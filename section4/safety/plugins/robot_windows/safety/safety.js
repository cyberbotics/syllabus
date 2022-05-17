import RobotWindow from 'https://cyberbotics.com/wwi/R2022b/RobotWindow.js';

// Initialize the RobotWindow class in order to communicate with the robot.
window.onload = function() {
  window.robotWindow = new RobotWindow();
  document.getElementById('clear').onclick = () => window.robotWindow.send('clear');
  document.getElementById('human').onclick = () => window.robotWindow.send('human');
  document.getElementById('barriers').onclick = () => window.robotWindow.send('barriers');
  document.getElementById('box').onclick = () => window.robotWindow.send('box');

  let distanceButton = document.getElementById('sensor');
  distanceButton.onclick = () => {
    window.robotWindow.send('sensor');
    if (distanceButton.clicked) {
      distanceButton.clicked = false;
      distanceButton.innerHTML = 'Enable a distance sensor on the manipulator.';
    } else {
      distanceButton.clicked = true;
      distanceButton.innerHTML = 'Disable the distance sensor on the manipulator.';
    }
  };

  let redButton = document.getElementById('button');
  redButton.onclick = () => {
    window.robotWindow.send('button');
    if (redButton.clicked) {
      redButton.clicked = false;
      redButton.innerHTML = 'Press the emergency stop button.';
    } else {
      redButton.clicked = true;
      redButton.innerHTML = 'Release the emergency stop button.';
    }
  };

  let speedButton = document.getElementById('speed');
  speedButton.onclick = () => {
    window.robotWindow.send('button');
    if (speedButton.clicked) {
      speedButton.clicked = false;
      speedButton.innerHTML = 'Decrease the speed of the manipulator.';
    } else {
      speedButton.clicked = true;
      speedButton.innerHTML = 'Increase the speed of the manipulator.';
    }
  };
};
