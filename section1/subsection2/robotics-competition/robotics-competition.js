import WebotsView from 'https://cyberbotics.com/wwi/R2022b/WebotsView.js';

let webotsView = new WebotsView();
document.body.appendChild(webotsView);
webotsView.onready = displayRobotWindow;
webotsView.connect('https://cyberbotics1.epfl.ch/1998/session?url=https://github.com/cyberbotics/syllabus/blob/main/section1/subsection2/robotics-competition/worlds/robotics_competition.wbt');
webotsView.showPlay = false;
webotsView.showReset = false;
webotsView.showQuit = false;
webotsView.showStep = false;
webotsView.showIde = false;
webotsView.showRobotWindow = false;

let showRobotWindow = true;

function displayRobotWindow() {
  if (webotsView._view && webotsView._view.x3dScene && webotsView._view.x3dScene.prefix) {
    let newDiv = document.createElement('div');
    newDiv.className = 'arrow-left';
    newDiv.id = 'arrow';
    let menuButton = document.createElement('button');
    menuButton.className = 'menu-button';
    menuButton.title = 'Show/Hide the robot window.';

    document.body.appendChild(menuButton);
    menuButton.appendChild(newDiv);

    if (document.getElementsByClassName('menu-button').length !== 0)
      document.getElementsByClassName('menu-button')[0].onclick = () => toggleRobotWindow();

    let serverUrl = webotsView._view.x3dScene.prefix;
    let url = serverUrl + 'robot_windows/competition_robot_window/competition_robot_window.html?name=robot';
    let iframe = document.createElement('iframe');
    iframe.src = url;
    iframe.id = 'iframe';
    document.body.appendChild(iframe);

    if (document.getElementById('fullscreenButton'))
      document.getElementById('fullscreenButton').onclick = () => toggleRobotComponentFullScreen();
    if (document.getElementById('partscreenButton')) {
      document.getElementById('partscreenButton').onclick = () => toggleRobotComponentFullScreen();
      document.getElementById('partscreenButton').style.display = 'none';
    }
    autoPlay();
  } else {
    setTimeout(function() {
      displayRobotWindow();
    }, 100);
  }
}

function toggleRobotComponentFullScreen(robot) {
  if (document.fullscreenElement) {
    document.getElementById('fullscreenButton').style.display = '';
    document.getElementById('partscreenButton').style.display = 'none';

    if (document.exitFullscreen)
      document.exitFullscreen();
  } else {
    document.getElementById('fullscreenButton').style.display = 'none';
    document.getElementById('partscreenButton').style.display = '';
    if (document.body.requestFullscreen)
      document.body.requestFullscreen();
  }
}

function autoPlay() {
  if (webotsView.toolbar)
    webotsView.toolbar._triggerPlayPauseButton();
  else
    setTimeout(() => autoPlay(), 100);
}

function toggleRobotWindow() {
  showRobotWindow = !showRobotWindow;
  updateRobotComponentDimension();

  let arrow = document.getElementById('arrow');
  if (arrow) {
    if (arrow.className === 'arrow-right')
      arrow.className = 'arrow-left';
    else if (arrow.className === 'arrow-left')
      arrow.className = 'arrow-right';
  }
}

function updateRobotComponentDimension() {
  const iframe = document.getElementById('iframe');
  if (document.getElementsByClassName('menu-button').length !== 0) {
    if (showRobotWindow === true) {
      iframe.style.display = '';
      webotsView.style.width = 'calc(100% - 350px)';
      webotsView.style.left = '350px';
      document.getElementsByClassName('menu-button')[0].style.left = '350px';
    } else {
      iframe.style.display = 'none';
      webotsView.style.width = '100%';
      webotsView.style.left = '0px';
      document.getElementsByClassName('menu-button')[0].style.left = '0px';
    }
  }
  webotsView.resize();
}
