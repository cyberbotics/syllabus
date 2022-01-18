import informationPanel from 'https://cyberbotics.com/wwi/R2022b/informationPanel.js';
import {quaternionToVec4, vec4ToQuaternion} from 'https://cyberbotics.com/wwi/R2022b/nodes/utils/utils.js';
import WbVector3 from 'https://cyberbotics.com/wwi/R2022b/nodes/utils/WbVector3.js';

let webotsView = document.getElementsByTagName('webots-view')[0];
document.getElementById('informationPlaceholder').innerHTML += informationPanel;

let showDeviceComponent = true;

let infoPanel = document.getElementsByClassName('information-panel')[0];

let category = document.createElement('div');
category.classList.add('device-category');
category.innerHTML = '<div class="device-title">' + 'Rotational Motor' + '</div>';
document.getElementById('device-component').appendChild(category);

let deviceDiv = document.createElement('div');
deviceDiv.classList.add('device');
// deviceDiv.addEventListener('mouseover', () => highlightX3DElement(robotName, deviceDiv));
deviceDiv.innerHTML = '<div class="device-name">' + 'Base Joint' + '</div>';
category.appendChild(deviceDiv);

let motorDiv = document.createElement('div');
motorDiv.classList.add('motor-component');
deviceDiv.appendChild(motorDiv);

let minLabel = document.createElement('div');
minLabel.classList.add('motor-label');
let maxLabel = document.createElement('div');
maxLabel.classList.add('motor-label');
minLabel.innerHTML = -3.14; // 2 decimals.
maxLabel.innerHTML = 3.14;

let slider = document.createElement('input');
slider.classList.add('motor-slider');
slider.setAttribute('type', 'range');
slider.setAttribute('step', 'any');
slider.setAttribute('min', -Math.PI);
slider.setAttribute('max', Math.PI);
slider.setAttribute('value', 0);
slider.setAttribute('webots-id', 164);
slider.setAttribute('webots-type', 'rotation');
slider.setAttribute('webots-axis', '0 0 1');
motorDiv.appendChild(minLabel);
motorDiv.appendChild(slider);
motorDiv.appendChild(maxLabel);

slider.addEventListener('input', () => sliderMotorCallback(slider, true));

deviceDiv = document.createElement('div');
deviceDiv.classList.add('device');
deviceDiv.innerHTML = '<div class="device-name">' + 'Other Joint' + '</div>';
category.appendChild(deviceDiv);

motorDiv = document.createElement('div');
motorDiv.classList.add('motor-component');
deviceDiv.appendChild(motorDiv);

minLabel = document.createElement('div');
minLabel.classList.add('motor-label');
maxLabel = document.createElement('div');
maxLabel.classList.add('motor-label');
minLabel.innerHTML = -0.8; // 2 decimals.
maxLabel.innerHTML = 0.8;

let slider2 = document.createElement('input');
slider2.classList.add('motor-slider');
slider2.setAttribute('type', 'range');
slider2.setAttribute('step', 'any');
slider2.setAttribute('min', -0.8);
slider2.setAttribute('max', 0.8);
slider2.setAttribute('value', 0);
slider2.setAttribute('webots-id', 101);
slider2.setAttribute('webots-type', 'rotation');
slider2.setAttribute('webots-axis', '-1 0 0.000796');
motorDiv.appendChild(minLabel);
motorDiv.appendChild(slider2);
motorDiv.appendChild(maxLabel);
slider2.addEventListener('input', () => sliderMotorCallback(slider2, true));

category = document.createElement('div');
category.classList.add('device-category');
category.innerHTML = '<div class="device-title">' + 'Linear Motor' + '</div>';
document.getElementById('device-component').appendChild(category);

deviceDiv = document.createElement('div');
deviceDiv.classList.add('device');
deviceDiv.innerHTML = '<div class="device-name">' + 'Other Joint' + '</div>';
category.appendChild(deviceDiv);

motorDiv = document.createElement('div');
motorDiv.classList.add('motor-component');
deviceDiv.appendChild(motorDiv);

minLabel = document.createElement('div');
minLabel.classList.add('motor-label');
maxLabel = document.createElement('div');
maxLabel.classList.add('motor-label');
minLabel.innerHTML = -0.01; // 2 decimals.
maxLabel.innerHTML = 0.01;

let slider3 = document.createElement('input');
slider3.classList.add('motor-slider');
slider3.setAttribute('type', 'range');
slider3.setAttribute('step', 'any');
slider3.setAttribute('min', -0.01);
slider3.setAttribute('max', 0.01);
slider3.setAttribute('value', 0);
slider3.setAttribute('webots-id', 223);
slider3.setAttribute('webots-type', 'translation');
slider3.setAttribute('webots-axis', '0 -4e-06 1');
motorDiv.appendChild(minLabel);
motorDiv.appendChild(slider3);
motorDiv.appendChild(maxLabel);
slider3.addEventListener('input', () => sliderMotorCallback(slider3, true));

if (document.getElementsByClassName('info-button').length !== 0)
  document.getElementsByClassName('info-button')[0].onclick = () => displayInformationWindow();
if (document.getElementsByClassName('menu-button').length !== 0)
  document.getElementsByClassName('menu-button')[0].onclick = () => toggleDeviceComponent();
if (document.getElementsByClassName('fullscreen-button').length !== 0)
  document.getElementsByClassName('fullscreen-button')[0].onclick = () => toggleRobotComponentFullScreen();
if (document.getElementsByClassName('exit-fullscreen-button').length !== 0) {
  document.getElementsByClassName('exit-fullscreen-button')[0].onclick = () => toggleRobotComponentFullScreen();
  document.getElementsByClassName('exit-fullscreen-button')[0].style.display = 'none';
}
if (document.getElementsByClassName('reset-button').length !== 0)
  document.getElementsByClassName('reset-button')[0].onclick = () => resetRobotComponent();

if (document.getElementsByClassName('robot-component').length !== 0) {
  document.getElementsByClassName('robot-component')[0].onmouseenter = () => showButtons();
  document.getElementsByClassName('robot-component')[0].onmouseleave = () => hideButtons();
}

function showButtons() {
  if (document.getElementsByClassName('info-button').length !== 0)
    document.getElementsByClassName('info-button')[0].style.display = '';

  if (document.getElementsByClassName('reset-button').length !== 0)
    document.getElementsByClassName('reset-button')[0].style.display = '';

  if (document.getElementsByClassName('fullscreen-button').length !== 0)
    document.getElementsByClassName('fullscreen-button')[0].style.display = '';

  if (document.getElementsByClassName('menu-button').length !== 0)
    document.getElementsByClassName('menu-button')[0].style.display = '';
}

function hideButtons() {
  if (document.getElementsByClassName('info-button').length !== 0)
    document.getElementsByClassName('info-button')[0].style.display = 'none';

  if (document.getElementsByClassName('reset-button').length !== 0)
    document.getElementsByClassName('reset-button')[0].style.display = 'none';

  if (document.getElementsByClassName('fullscreen-button').length !== 0)
    document.getElementsByClassName('fullscreen-button')[0].style.display = 'none';

  if (document.getElementsByClassName('exit-fullscreen-button').length !== 0)
    document.getElementsByClassName('exit-fullscreen-button')[0].style.display = 'none';

  if (document.getElementsByClassName('menu-button').length !== 0)
    document.getElementsByClassName('menu-button')[0].style.display = 'none';
}

function toggleDeviceComponent() {
  showDeviceComponent = !showDeviceComponent;
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
  const deviceMenu = document.getElementById('device-component');
  const robotView = document.getElementById('robot-view');

  if (showDeviceComponent === true) {
    deviceMenu.style.display = '';
    robotView.style.width = '70%';
  } else {
    deviceMenu.style.display = 'none';
    robotView.style.width = '100%';
  }

  webotsView.resize();
}

function toggleRobotComponentFullScreen(robot) {
  if (document.fullscreenElement) {
    document.getElementsByClassName('fullscreen-button')[0].style.display = '';
    document.getElementsByClassName('exit-fullscreen-button')[0].style.display = 'none';

    if (document.exitFullscreen)
      document.exitFullscreen();
  } else {
    document.getElementsByClassName('fullscreen-button')[0].style.display = 'none';
    document.getElementsByClassName('exit-fullscreen-button')[0].style.display = '';

    if (document.getElementById('robot-component').requestFullscreen) {
      document.getElementById('robot-component').requestFullscreen();
      document.addEventListener('fullscreenchange', function() {
        updateRobotComponentDimension();
      });
    }
  }
}

function resetRobotComponent(robot) {
  // unhighlightX3DElement(robot);

  // Reset the motor sliders.
  let sliders = document.getElementsByClassName('motor-slider');
  for (let s = 0; s < sliders.length; s++) {
    let slider = sliders[s];
    // if the attribute is not present, it means that the slider was not moved
    if (slider.hasAttribute('initialValue')) {
      slider.value = slider.getAttribute('initialValue');
      sliderMotorCallback(slider);
    }
  }

  webotsView.resetViewpoint();
  //  No need to force a render as it is already done in webotsView.resetViewpoint
}

function sliderMotorCallback(slider, render) {
  //  The first time the slider is moved, save the initial value for reset.
  if (!slider.hasAttribute('initialValue')) {
    let type = slider.getAttribute('webots-type');
    if (type === 'rotation')
      slider.setAttribute('initialValue', webotsView.getNode(slider.getAttribute('webots-id')).rotation.toString());
    else if (type === 'translation')
      slider.setAttribute('initialValue', webotsView.getNode(slider.getAttribute('webots-id')).translation.toString());
  }

  let value = parseFloat(slider.value);
  let axis = slider.getAttribute('webots-axis').split(/[\s,]+/);
  axis = glm.vec3(parseFloat(axis[0]), parseFloat(axis[1]), parseFloat(axis[2]));
  switch (slider.getAttribute('webots-type')) {
    case 'rotation':
      let init = slider.getAttribute('initialValue');
      if (!init)
        init = '0 0 1 0';
      init = init.split(/\s/);
      init = {'x': parseFloat(init[0]), 'y': parseFloat(init[1]), 'z': parseFloat(init[2]), 'w': parseFloat(init[3])};
      let q = glm.angleAxis(value, axis);
      q = q.mul(vec4ToQuaternion(init));
      webotsView.updateNode(slider.getAttribute('webots-id'), 'rotation', quaternionToVec4(q).toString(), render);
      break;
    case 'translation':
      let initialValue = slider.getAttribute('initialValue');
      if (!initialValue)
        initialValue = '0 0 0';
      initialValue = initialValue.split(/\s/);
      initialValue = new WbVector3(parseFloat(initialValue[0]), parseFloat(initialValue[1]), parseFloat(initialValue[2]));
      let translation = initialValue.add(axis.mul(value));
      webotsView.updateNode(slider.getAttribute('webots-id'), 'translation', translation.toString(), render);
      break;
  }
}

function displayInformationWindow() {
  if (infoPanel) {
    if (infoPanel.style.display === 'block')
      infoPanel.style.display = 'none';
    else
      infoPanel.style.display = 'block';
  }
}

window.addEventListener('click', function(e) {
  if (infoPanel && !infoPanel.contains(e.target) && !document.getElementsByClassName('info-button')[0].contains(e.target))
    infoPanel.style.display = 'none';
});

// let button = document.getElementById('reset');
// button.onclick = () => {
//   webotsView.updateNode('83', 'rotation', slider.getAttribute('initialValue'));
// }
