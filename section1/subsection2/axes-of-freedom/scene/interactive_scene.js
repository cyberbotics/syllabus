import WbPBRAppearance from 'https://cyberbotics.com/wwi/R2022b/nodes/WbPBRAppearance.js';
import WbShape from 'https://cyberbotics.com/wwi/R2022b/nodes/WbShape.js';
import WbCylinder from 'https://cyberbotics.com/wwi/R2022b/nodes/WbCylinder.js';
import WbTransform from 'https://cyberbotics.com/wwi/R2022b/nodes/WbTransform.js';
import WbVector3 from 'https://cyberbotics.com/wwi/R2022b/nodes/utils/WbVector3.js';
import WbVector4 from 'https://cyberbotics.com/wwi/R2022b/nodes/utils/WbVector4.js';
import WbWorld from 'https://cyberbotics.com/wwi/R2022b/nodes/WbWorld.js';
import {quaternionToVec4, vec4ToQuaternion, getAnId} from 'https://cyberbotics.com/wwi/R2022b/nodes/utils/utils.js';

let webotsView = document.getElementsByTagName('webots-view')[0];

let showDeviceComponent = true;

let pointer;
let pointedID;

let category = document.createElement('div');
category.classList.add('device-category');
category.innerHTML = '<div class="device-title">' + 'Rotational Motor' + '</div>';
document.getElementById('device-component').appendChild(category);

createRotationalSlider('Shoulder pan joint', category, -6.28, 6.28, 389, '0 0 1');
createRotationalSlider('Shoulder lift joint', category, -3.92, 0.78, 408, '0 1 0');
createRotationalSlider('Elbow joint', category, -2.8, 2.8, 447, '0 1 0');
createRotationalSlider('Wrist first joint', category, -6.28, 6.28, 478, '0 1 0');
createRotationalSlider('Wrist second joint', category, -6.28, 6.28, 497, '0 0 1');
createRotationalSlider('Wrist third joint', category, -6.28, 6.28, 516, '0 1 0');

if (document.getElementsByClassName('menu-button').length !== 0)
  document.getElementsByClassName('menu-button')[0].onclick = () => toggleDeviceComponent();

if (document.getElementsByClassName('robot-component').length !== 0) {
  document.getElementsByClassName('robot-component')[0].onmouseenter = () => showButton();
  document.getElementsByClassName('robot-component')[0].onmouseleave = () => hideButton();
}

buttonHandler();

function buttonHandler() {
  if (webotsView.hasScene()) {
    if (document.getElementsByClassName('fullscreen-button').length !== 0)
      document.getElementsByClassName('fullscreen-button')[0].onclick = () => toggleRobotComponentFullScreen();
    if (document.getElementsByClassName('exit-fullscreen-button').length !== 0) {
      document.getElementsByClassName('exit-fullscreen-button')[0].onclick = () => toggleRobotComponentFullScreen();
      document.getElementsByClassName('exit-fullscreen-button')[0].style.display = 'none';
    }

    if (document.getElementsByClassName('reset-button').length !== 0)
      document.getElementsByClassName('reset-button')[0].onclick = () => resetRobotComponent();
  } else
    setTimeout(() => buttonHandler(), 100);
}

function createRotationalSlider(name, category, minVal, maxVal, id, axis) {
  let deviceDiv = document.createElement('div');
  deviceDiv.classList.add('device');
  deviceDiv.setAttribute('webots-id', id);
  deviceDiv.setAttribute('webots-axis', axis);
  deviceDiv.addEventListener('mouseover', () => highlightX3DElement(deviceDiv));
  deviceDiv.innerHTML = '<div class="device-name">' + name + '</div>';
  category.appendChild(deviceDiv);

  let motorDiv = document.createElement('div');
  motorDiv.classList.add('motor-component');
  deviceDiv.appendChild(motorDiv);

  let minLabel = document.createElement('div');
  minLabel.classList.add('motor-label');
  let maxLabel = document.createElement('div');
  maxLabel.classList.add('motor-label');
  minLabel.innerHTML = minVal;
  maxLabel.innerHTML = maxVal;

  let slider = document.createElement('input');
  slider.classList.add('motor-slider');
  slider.setAttribute('type', 'range');
  slider.setAttribute('step', 'any');
  slider.setAttribute('min', minVal);
  slider.setAttribute('max', maxVal);
  slider.setAttribute('value', 0);
  slider.setAttribute('webots-id', id);
  slider.setAttribute('webots-type', 'rotation');
  slider.setAttribute('webots-axis', axis);
  motorDiv.appendChild(minLabel);
  motorDiv.appendChild(slider);
  motorDiv.appendChild(maxLabel);
  slider.addEventListener('input', () => sliderMotorCallback(slider, true));
}

function highlightX3DElement(deviceElement) {
  let id = deviceElement.getAttribute('webots-id');
  if (id === pointedID)
    return;

  unhighlightX3DElement();

  pointedID = id;

  if (typeof WbWorld.instance === 'undefined')
    return;
  let object = WbWorld.instance.nodes.get('n' + id);
  if (object) {
    if (typeof WbWorld.instance !== 'undefined' && typeof pointer === 'undefined') {
      let geom = new WbCylinder(getAnId(), 0.0008, 0.5, 36, true, true, true);
      WbWorld.instance.nodes.set(geom.id, geom);
      let pbr = new WbPBRAppearance(getAnId(), new WbVector3(1, 0, 0), undefined, 0, 1, undefined, 0, undefined,
        1, undefined, 1, undefined, 1, new WbVector3(0, 0, 0), undefined, 1, undefined);
      WbWorld.instance.nodes.set(pbr.id, pbr);
      let shape = new WbShape(getAnId(), false, false, geom, pbr);
      WbWorld.instance.nodes.set(shape.id, shape);
      geom.parent = shape.id;
      pbr.parent = shape.id;
      let axis = new WbVector4();
      switch (id) {
        case '408':
        case '447':
        case '478':
        case '516':
          axis = new WbVector4(1, 0, 0, 1.5708);
          break;
      }
      pointer = new WbTransform(getAnId(), false, new WbVector3(0, 0, 0), new WbVector3(1, 1, 1), axis);
      pointer.children.push(shape);
      WbWorld.instance.nodes.set(pointer.id, pointer);
      shape.parent = pointer.id;
    }

    object.children.push(pointer);
    pointer.parent = object.id;
    pointer.finalize();

    webotsView._view.x3dScene.render();
  }
}

function unhighlightX3DElement(robot) {
  removePointer();
  webotsView._view.x3dScene.render();
  pointedID = undefined;
}

function removePointer() {
  if (typeof pointer !== 'undefined') {
    pointer.delete();
    pointer = undefined;
  }
}

function showButton() {
  if (document.getElementsByClassName('menu-button').length !== 0)
    document.getElementsByClassName('menu-button')[0].style.display = '';
}

function hideButton() {
  if (document.getElementsByClassName('menu-button').length !== 0)
    document.getElementsByClassName('menu-button')[0].style.display = 'none';

  unhighlightX3DElement();
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
  unhighlightX3DElement();

  // Reset the motor sliders.
  let sliders = document.getElementsByClassName('motor-slider');
  for (let s = 0; s < sliders.length; s++) {
    let slider = sliders[s];
    // if the attribute is not present, it means that the slider was not moved
    if (slider.hasAttribute('initialValue')) {
      slider.value = 0;
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
    if (type === 'rotation' && webotsView.getNode(slider.getAttribute('webots-id')))
      slider.setAttribute('initialValue', webotsView.getNode(slider.getAttribute('webots-id')).rotation.toString());
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
      renderX10();
      break;
  }
}

// To get rid of gtao artifact
async function renderX10() {
  if (webotsView) {
    for (let i = 0; i < 10; i++) {
      setTimeout(function() {
        webotsView._view.x3dScene.render();
      }, 40 * i);
    };
  }
}
