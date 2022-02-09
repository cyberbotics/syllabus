import RobotWindow from 'https://cyberbotics.com/wwi/R2022b/RobotWindow.js';

// Initialize the RobotWindow class in order to communicate with the robot.
window.onload = function() {
  window.robotWindow = new RobotWindow();
  document.getElementById('waterbottle').onclick = () => window.robotWindow.send('waterbottle');
  let storageButton = document.getElementById('storage');
  storageButton.onclick = () => {
    window.robotWindow.send('storage');
    storageButton.disabled = true;
    storageButton.className = 'button-disable';
  };
  let boxButton = document.getElementById('cardboardBox');
  boxButton.onclick = () => {
    window.robotWindow.send('cardboardBox');
    boxButton.disabled = true;
    boxButton.className = 'button-disable';
  };
};
