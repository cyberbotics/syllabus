import Terminal from '../resources/Terminal.js';

const config = {
  settings: {
    showPopoutIcon: true
  },
  content: [{
    type: 'row',
    content: [{
      type: 'column',
      width: 50,
      content: [{
        type: 'component',
        height: 70,
        componentName: 'InformationWindow',
        componentState: {
          label: 'Information'
        }
      }, {
        type: 'component',
        componentName: 'Terminal'
      }]
    }, {
      type: 'column',
      content: [ {
        type: 'component',
        componentName: 'WebotsView',
        componentState: {
          label: 'A'
        }
      }, {
        type: 'component',
        componentName: 'IDE',
        componentState: {
          label: 'B'
        }
      }]
    }]
  }]
};

let webotsView;
let terminalDiv;
let informationWindow;
let minimizedStorage = document.getElementById('minimizedContent');

let haveWebotsView = 1;
let haveInformationWindow = 1;
let haveIDE = 1;
let haveTerminal = 1;
let haveRobotWindow = 0;

let terminal; // TODO put in a web component with terminalDiv
let iframeDisplayed = false;
let iframeUrl;
let rwIframeUrl;
let myLayout = new GoldenLayout(config, $(layoutContainer));
window.addEventListener('resize', () => myLayout._resizeFunction());

function create(container) {
  if (typeof webotsView === 'undefined') {
    webotsView = document.createElement('webots-view');
    webotsView.id = 'webotsView';
    webotsView.showQuit = false;
    webotsView.showIde = false;
    webotsView.showRobotWindow = false;
    webotsView.onready = onConnect;
    webotsView.connect('https://simulation.webots.cloud:8443/1998/session?url=https://github.com/cyberbotics/syllabus/tree/main/section2/4PositionOfRobot/worlds/obstacle_avoidance.wbt', undefined, undefined, undefined, 900);
    // webotsView.connect('ws://localhost:1234');
  }
  container.getElement().html(webotsView);
}

function onConnect() {
  if (webotsView._view && webotsView._view.x3dScene && webotsView._view.x3dScene.prefix && !iframeDisplayed) {
    let serverUrl = webotsView._view.x3dScene.prefix;
    let url = serverUrl;
    const elements = url.split('/').filter(element => element);
    let portString = elements[elements.length - 1];
    let port = parseFloat(portString) + 500;
    iframeUrl = url.replace(portString, port) + '#/home/project/webots-project/';
    let iframe = document.createElement('iframe');
    iframe.src = iframeUrl;
    iframe.style.width = '100%';
    iframe.style.height = '100%';
    document.getElementById('idePlaceHolder').appendChild(iframe);

    let rwIframe = document.createElement('iframe');
    rwIframeUrl = serverUrl + 'robot_windows/generic/generic.html?name=Thymio%20II';
    rwIframe.src = rwIframeUrl;
    rwIframe.style.width = '100%';
    rwIframe.style.height = '100%';
    rwIframe.style.backgroundColor = 'white';
    document.getElementById('idePlaceHolder').appendChild(rwIframe);
    iframeDisplayed = true;
  } else {
    setTimeout(function() {
      onConnect();
    }, 100);
  }
}

myLayout.registerComponent('WebotsView', function(container, componentState) {
  create(container);
  container.on('resize', () => webotsView.resize());
  container.on('tab', () => container.tab.setTitle('Simulation'));
  container.on('destroy', () => {
    let img = document.getElementById('imgWebotsView');
    if (img)
      img.src = '../resources/icons/WebotsView_grey.png';
    if (minimizedStorage)
      minimizedStorage.appendChild(webotsView);
    haveWebotsView = 0;
    webotsView.style.display = 'none';
  });

  webotsView.style.display = 'block';
  let img = document.getElementById('imgWebotsView');
  if (img)
    img.src = '../resources/icons/WebotsView_white.png';
  haveWebotsView = 1;
});

myLayout.registerComponent('IDE', function(container, componentState) {
  if (iframeDisplayed)
    container.getElement().html('<div id=idePlaceHolder style="width:90%;height:100%;"><iframe src=' + iframeUrl + ' style="width:100%;height:100%";></iframe></div>');
  else
    container.getElement().html('<div id=idePlaceHolder style="width:100%;height:100%;"></div>');
  container.on('destroy', () => {
    let img = document.getElementById('imgIDE');
    if (img)
      img.src = '../resources/icons/IDE_grey.png';
    haveIDE = 0;
  });
  let img = document.getElementById('imgIDE');
  if (img)
    img.src = '../resources/icons/IDE_white.png';
  haveIDE = 1;
});

myLayout.registerComponent('InformationWindow', function(container, componentState) {
  if (typeof informationWindow === 'undefined') {
    informationWindow = document.createElement('iframe');
    informationWindow.src = 'instructions.html';
    informationWindow.height = '100%';
    informationWindow.width = '100%';
  }

  container.getElement().html(informationWindow);
  container.on('tab', () => container.tab.setTitle('Information'));
  container.on('destroy', () => {
    let img = document.getElementById('imgInformationWindow');
    if (img)
      img.src = '../resources/icons/InformationWindow_grey.png';
    if (minimizedStorage)
      minimizedStorage.appendChild(informationWindow);
    informationWindow.style.display = 'none';
    haveInformationWindow = 0;
  });

  informationWindow.style.display = 'block';
  haveInformationWindow = 1;
  let img = document.getElementById('imgInformationWindow');
  if (img)
    img.src = '../resources/icons/InformationWindow_white.png';
});

myLayout.registerComponent('RobotWindow', function(container, componentState) {
  if (iframeDisplayed)
    container.getElement().html('<div id=rwPlaceHolder style="width:100%;height:100%;"><iframe src=' + rwIframeUrl + ' style="width:100%;height:100%;background-color:white"></iframe></div>');
  else
    container.getElement().html('<div id=rwPlaceHolder style="width:100%;height:100%;"></div>');

  container.on('tab', () => container.tab.setTitle('Robot Window'));
  container.on('destroy', () => {
    let img = document.getElementById('imgRobotWindow');
    if (img)
      img.src = '../resources/icons/RobotWindow_grey.png';
    haveRobotWindow = 0;
  });

  haveRobotWindow = 1;
  let img = document.getElementById('imgRobotWindow');
  if (img)
    img.src = '../resources/icons/RobotWindow_white.png';
});


myLayout.registerComponent('Terminal', function(container, componentState) {
  if (typeof terminal === 'undefined') {
    terminalDiv = document.createElement('div');
    terminalDiv.id = 'terminal';
    terminalDiv.style.color = 'white';
    terminalDiv.style.fontFamily = 'Lucida Console';
    if (typeof terminal === 'undefined')
      terminal = new Terminal();
    tryToConnectTerminal();
  }

  container.getElement().html(terminalDiv);
  container.on('destroy', () => {
    container.getElement().html(terminalDiv);
    let img = document.getElementById('imgTerminal');
    if (img)
      img.src = '../resources/icons/Terminal_grey.png';
    if (minimizedStorage)
      minimizedStorage.appendChild(terminalDiv);
    terminalDiv.style.display = 'none';
    haveTerminal = 0;
  });

  terminalDiv.style.display = 'block';
  setTerminalOverflow();

  let img = document.getElementById('imgTerminal');
  if (img)
    img.src = '../resources/icons/Terminal_white.png';
  haveTerminal = 1;
});

myLayout.init();

function setTerminalOverflow() {
  if (document.getElementById('terminal'))
    document.getElementById('terminal').parentNode.style.overflow = 'auto';
  else
    setTimeout(() => setTerminalOverflow(), 100);
}

let addMenuItem = function(name) {
  let buttonTitle;
  switch (name) {
    case 'WebotsView':
      buttonTitle = 'Simulation';
      break;
    case 'InformationWindow':
      buttonTitle = 'Information';
      break;
    case 'IDE':
      buttonTitle = 'IDE';
      break;
    case 'Terminal':
      buttonTitle = 'Terminal';
      break;
    case 'RobotWindow':
      buttonTitle = 'Robot window';
      break;
  }
  let element = $('<button class="side-menu-button"><img id=img' + name + ' src=../resources/icons/' + name + '_white.png width=40px style=transparency/><div class="buttonInfo">' + buttonTitle + '</div></button>');
  element.html = 'salut';
  $('#menuContainer').append(element);
  let newItemConfig = {
    type: 'component',
    componentName: name,
    componentState: {
      text: 'New ' + name
    }
  };

  element.click(function() {
    switch (name) {
      case 'WebotsView':
        if (haveWebotsView === 1) {
          $("[title|='Simulation']").find('.lm_close_tab').click();
          return;
        }
        break;
      case 'IDE':
        if (haveIDE === 1) {
          $("[title|='IDE']").find('.lm_close_tab').click();
          return;
        }
        break;
      case 'InformationWindow':
        if (haveInformationWindow === 1) {
          $("[title|='Information']").find('.lm_close_tab').click();
          return;
        }
        break;
      case 'Terminal':
        if (haveTerminal === 1) {
          $("[title|='Terminal']").find('.lm_close_tab').click();
          return;
        }
        break;
      case 'RobotWindow':
        if (haveRobotWindow === 1) {
          $("[title|='Robot Window']").find('.lm_close_tab').click();
          return;
        }
        break;
    }
    if (myLayout.root.contentItems[0])
      myLayout.root.contentItems[0].addChild(newItemConfig);
    else
      myLayout.root.addChild(newItemConfig);
  });
};
addMenuItem('WebotsView');
addMenuItem('InformationWindow');
addMenuItem('IDE');
addMenuItem('Terminal');
addMenuItem('RobotWindow');
if (!haveRobotWindow) {
  let img = document.getElementById('imgRobotWindow');
  if (img)
    img.src = '../resources/icons/RobotWindow_grey.png';
}

const fullscreenButton = $('<button class="side-menu-button" id="fullscreenGlobal" style="bottom:0px;left:9px;position:absolute;"><img id=img' + name + ' src=../resources/icons/fullscreen.png width=40px style=transparency/><div class="buttonInfo">Full screen</div></button>');
$('#menuContainer').append(fullscreenButton);
const exitFullscreenButton = $('<button class="side-menu-button" id="partscreenGlobal" style="bottom:0px;left:9px;position:absolute;"><img id=img' + name + ' src=../resources/icons/exitfullscreen.png width=40px style=transparency/><div class="buttonInfo">Exit full screen</div></button>');
$('#menuContainer').append(exitFullscreenButton);

if (document.getElementById('fullscreenGlobal'))
  document.getElementById('fullscreenGlobal').onclick = () => toggleRobotComponentFullScreen();
if (document.getElementById('partscreenGlobal')) {
  document.getElementById('partscreenGlobal').onclick = () => toggleRobotComponentFullScreen();
  document.getElementById('partscreenGlobal').style.display = 'none';
}
function tryToConnectTerminal() {
  if (typeof terminal !== 'undefined' && typeof webotsView !== 'undefined' && webotsView.hasView()) {
    webotsView.setWebotsMessageCallback(_ => terminal.createMessage(_));
    webotsView.setWebotsErrorMessageCallback(_ => terminal.createErrorMessage(_));
  } else {
    setTimeout(function() {
      tryToConnectTerminal();
    }, 100);
  }
}

function toggleRobotComponentFullScreen() {
  if (document.fullscreenElement) {
    if (document.exitFullscreen)
      document.exitFullscreen();
  } else {
    if (document.body.requestFullscreen)
      document.body.requestFullscreen();
  }
}

function onFullscreenChange() {
  if (!document.fullscreenElement) {
    document.getElementById('fullscreenGlobal').style.display = '';
    document.getElementById('partscreenGlobal').style.display = 'none';
  } else {
    document.getElementById('fullscreenGlobal').style.display = 'none';
    document.getElementById('partscreenGlobal').style.display = '';
  }
}

document.addEventListener('fullscreenchange', () => onFullscreenChange());

window.addEventListener('beforeunload', e => {
  e.preventDefault();
  const message =
    'If you leave or reload the page, all your code will be lost. Do you want to continue?';
  e.returnValue = message;
  return message;
});
