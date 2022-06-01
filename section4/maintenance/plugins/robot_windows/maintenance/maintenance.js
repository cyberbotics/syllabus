import RobotWindow from 'https://cyberbotics.com/wwi/R2022b/RobotWindow.js';

// Initialize the RobotWindow class in order to communicate with the robot.
window.onload = function() {
  const fingerButton = document.getElementById('finger');
  fingerButton.disabled = true;
  const calibrateButton = document.getElementById('calibrate');
  calibrateButton.disabled = true;
  const lubricateButton = document.getElementById('oil');
  lubricateButton.disabled = true;
  const cameraButton = document.getElementById('camera');
  cameraButton.disabled = true;

  window.robotWindow = new RobotWindow();

  const cycleButton = document.getElementById('cycle');
  cycleButton.onclick = () => {
    window.robotWindow.send('cycle');
  };

  const prepareButton = document.getElementById('prepare');
  prepareButton.onclick = () => {
    window.robotWindow.send('prepare');
    if (prepareButton.clicked) {
      prepareButton.clicked = false;
      disableButton(fingerButton);
      disableButton(calibrateButton);
      disableButton(lubricateButton);
      disableButton(cameraButton);
      enableButton(cycleButton);
      prepareButton.innerHTML = 'Prepare the robot for a human intervention.';
    } else {
      prepareButton.clicked = true;
      enableButton(fingerButton);
      enableButton(calibrateButton);
      enableButton(lubricateButton);
      enableButton(cameraButton);
      disableButton(cycleButton);
      prepareButton.innerHTML = 'Restart the robot.';
    }
  };

  fingerButton.onclick = () => {
    window.robotWindow.send('finger');
    disableButton(fingerButton);
    fingerButton.repaired = true;
  };

  calibrateButton.onclick = () => {
    window.robotWindow.send('calibrate');
    disableButton(calibrateButton);
    calibrateButton.repaired = true;
  };

  lubricateButton.onclick = () => {
    window.robotWindow.send('oil');
    disableButton(lubricateButton);
    lubricateButton.repaired = true;
  };

  cameraButton.onclick = () => {
    window.robotWindow.send('camera');
    disableButton(cameraButton);
    cameraButton.repaired = true;
  };

  function enableButton(button) {
    if (typeof button.repaired === 'undefined') {
      button.className = 'button-enable';
      button.disabled = false;
    }
  }

  function disableButton(button) {
    button.disabled = true;
    button.className = 'button-disable';
  }
};
