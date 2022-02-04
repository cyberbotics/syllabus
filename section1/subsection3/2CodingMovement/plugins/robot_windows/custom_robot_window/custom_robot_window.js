import RobotWindow from 'https://cyberbotics.com/wwi/R2022b/RobotWindow.js';

let dataPoints = [];
let chart;
let time = 0;
// A message coming from the robot has been received.
function receive(message, robot) {
  if (message.startsWith('velocity: ')) {
    message = message.substr(9).split(',');
    let velocity = Math.abs(parseFloat(message[0]));
    let time = parseFloat(message[1]);
    updateChart(time, velocity);
  }
}

// Initialize the RobotWindow class in order to communicate with the robot.
window.onload = function() {
  window.robotWindow = new RobotWindow();
  window.robotWindow.setTitle('Custom HTML robot window');
  window.robotWindow.receive = receive;

  chart = new CanvasJS.Chart('chartContainer', {
    axisY: {
      title: 'Velocity [m/s]',
      maximum: 0.3
    },
    axisX: {
      title: 'Time [s]',
      maximum: 6
    },
    data: [{
      type: 'line',
      dataPoints: dataPoints,
      markerType: 'line',
      lineThickness: 4
    }]
  });

  updateChart(0, 0);
};

function updateChart(x, y) {
  time += (x / 1000);
  console.log(time + ' , ' + y);
  dataPoints.push({
    x: time,
    y: y
  });
  chart.render();
};
