import RobotWindow from 'https://cyberbotics.com/wwi/R2022b/RobotWindow.js';

// Initialize the RobotWindow class in order to communicate with the robot.
window.onload = function() {
  window.robotWindow = new RobotWindow();
  document.getElementById('human').onclick = () => window.robotWindow.send('human');
  document.getElementById('barriers').onclick = () => window.robotWindow.send('barriers');
  document.getElementById('box').onclick = () => window.robotWindow.send('box');

  const humanButton = document.getElementById('human');
  humanButton.onclick = () => {
    window.robotWindow.send('human');
    if (humanButton.clicked) {
      humanButton.clicked = false;
      humanButton.innerHTML = 'Add a human worker.';
    } else {
      humanButton.clicked = true;
      humanButton.innerHTML = 'Remove the human worker.';
    }
  };

  const barrierButton = document.getElementById('barriers');
  barrierButton.onclick = () => {
    window.robotWindow.send('barriers');
    if (barrierButton.clicked) {
      barrierButton.clicked = false;
      barrierButton.innerHTML = 'Add barriers.';
    } else {
      barrierButton.clicked = true;
      barrierButton.innerHTML = 'Remove barriers.';
      const boxButton = document.getElementById('box');
      if (boxButton.clicked) {
        boxButton.clicked = false;
        boxButton.innerHTML = 'Add a isolation box.';
      }
    }
  };

  const boxButton = document.getElementById('box');
  boxButton.onclick = () => {
    window.robotWindow.send('box');
    if (boxButton.clicked) {
      boxButton.clicked = false;
      boxButton.innerHTML = 'Add a isolation box.';
    } else {
      boxButton.clicked = true;
      boxButton.innerHTML = 'Remove the isolation box.';
      const barrierButton = document.getElementById('barriers');
      if (barrierButton.clicked) {
        barrierButton.clicked = false;
        barrierButton.innerHTML = 'Add barriers.';
      }
    }
  };

  const distanceButton = document.getElementById('sensor');
  distanceButton.onclick = () => {
    window.robotWindow.send('sensor');
    if (distanceButton.clicked) {
      distanceButton.clicked = false;
      distanceButton.innerHTML = 'Enable the distance sensors on the manipulator.';
    } else {
      distanceButton.clicked = true;
      distanceButton.innerHTML = 'Disable the distance sensors on the manipulator.';
    }
  };

  const redButton = document.getElementById('button');
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

  const speedButton = document.getElementById('speed');
  speedButton.onclick = () => {
    window.robotWindow.send('speed');
    if (speedButton.clicked) {
      speedButton.clicked = false;
      speedButton.innerHTML = 'Decrease the speed of the manipulator.';
    } else {
      speedButton.clicked = true;
      speedButton.innerHTML = 'Increase the speed of the manipulator.';
    }
  };
};
