import Terminal from './Terminal.js';

const config = {
  settings: {
    showPopoutIcon: true
  },
  content: [{
    type: 'row',
    content: [{
      type: 'column',
      width: 70,
      content: [{
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
    }, {
      type: 'column',
      content: [{
        type: 'component',
        height: 60,
        componentName: 'RobotWindow',
        componentState: {
          label: 'Information'
        }
      }, {
        type: 'component',
        componentName: 'Terminal'
      }]
    }]
  }]
};

let webotsView;
let terminalDiv;
let robotWindow;
let minimizedStorage = document.getElementById('minimizedContent');

let haveWebotsView = 1;
let haveRobotWindow = 1;
let haveIDE = 1;
let haveTerminal = 1;

let terminal; // TODO put in a web component with terminalDiv
let iframeDisplayed = false;
let iframeUrl;
let myLayout = new GoldenLayout(config, $(layoutContainer));
window.addEventListener('resize', () => myLayout._resizeFunction());

function create(container) {
  if (typeof webotsView === 'undefined') {
    webotsView = document.createElement('webots-view');
    webotsView.id = 'webotsView';
    webotsView.showQuit = false;
    // webotsView.connect("wss://cyberbotics1.epfl.ch/1999/session?url=file:///home/cyberbotics/webots/projects/robots/softbank/nao/worlds/nao_room.wbt");
    // webotsView.loadAnimation('https://benjamindeleze.github.io/sandbox/animations/pr2.x3d', 'https://benjamindeleze.github.io/sandbox/animations/pr2.json');
    webotsView.connect('https://cyberbotics1.epfl.ch/1998/session?url=https://github.com/cyberbotics/syllabus/tree/main/section2/2StartUpProcedure/worlds/industrial_example.wbt', 'x3d', false, false, onConnect);
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
      img.src = 'icons/WebotsView_grey.png';
    if (minimizedStorage)
      minimizedStorage.appendChild(webotsView);
    haveWebotsView = 0;
    webotsView.style.display = 'none';
  });

  webotsView.style.display = 'block';
  let img = document.getElementById('imgWebotsView');
  if (img)
    img.src = 'icons/WebotsView_white.png';
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
      img.src = 'icons/IDE_grey.png';
    haveIDE = 0;
  });
  let img = document.getElementById('imgIDE');
  if (img)
    img.src = 'icons/IDE_white.png';
  haveIDE = 1;
});

myLayout.registerComponent('RobotWindow', function(container, componentState) {
  if (typeof robotWindow === 'undefined') {
    robotWindow = document.createElement('iframe');
    robotWindow.src = 'instructions.html';
    robotWindow.height = '100%';
    robotWindow.width = '100%';
  }

  container.getElement().html(robotWindow);
  container.on('tab', () => container.tab.setTitle('Information Window'));
  container.on('destroy', () => {
    let img = document.getElementById('imgRobotWindow');
    if (img)
      img.src = 'icons/RobotWindow_grey.png';
    if (minimizedStorage)
      minimizedStorage.appendChild(robotWindow);
    robotWindow.style.display = 'none';
    haveRobotWindow = 0;
  });

  robotWindow.style.display = 'block';
  haveRobotWindow = 1;
  let img = document.getElementById('imgRobotWindow');
  if (img)
    img.src = 'icons/RobotWindow_white.png';
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
      img.src = 'icons/Terminal_grey.png';
    if (minimizedStorage)
      minimizedStorage.appendChild(terminalDiv);
    terminalDiv.style.display = 'none';
    haveTerminal = 0;
  });

  terminalDiv.style.display = 'block';
  let img = document.getElementById('imgTerminal');
  if (img)
    img.src = 'icons/Terminal_white.png';
  haveTerminal = 1;
});

myLayout.init();
document.getElementById('terminal').parentNode.style.overflow = 'auto';

let addMenuItem = function(name) {
  let element = $('<button class="side-menu-button"><img id=img' + name + ' src=icons/' + name + '_white.png width=40px style=transparency/><div class="buttonInfo">' + name + '</div></button>');
  $('#menuContainer').append(element);
  let newItemConfig = {
    type: 'component',
    componentName: name,
    componentState: {
      text: 'New ' + name
    }
  };

  element.click(function() {
    console.log(name)
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
      case 'RobotWindow':
        if (haveRobotWindow === 1) {
          $("[title|='Information Window']").find('.lm_close_tab').click();
          return;
        }
        break;
      case 'Terminal':
        if (haveTerminal === 1) {
          $("[title|='Terminal']").find('.lm_close_tab').click();
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
addMenuItem('RobotWindow');
addMenuItem('IDE');
addMenuItem('Terminal');

function tryToConnectTerminal() {
  if (typeof terminal !== 'undefined' && webotsView.hasView()) {
    webotsView.setWebotsMessageCallback(_ => terminal.createMessage(_));
    webotsView.setWebotsErrorMessageCallback(_ => terminal.createErrorMessage(_));
  } else {
    setTimeout(function() {
      tryToConnectTerminal();
    }, 100);
  }
}
