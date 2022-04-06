export default class Terminal {
  constructor(parentNode) {
    this.ansiUp = new AnsiUp();
    this.textIDs = [];
    this.currentID = 0;

    document.addEventListener('keydown', e => {
      if (e.ctrlKey && e.code === 'KeyL') {
        e.preventDefault();
        this.textIDs = [];
        this.currentID = 0;
        let terminal = document.getElementById('terminal');
        if (terminal)
          terminal.innerHTML = '';
      }
    });
  }

  createMessage(msg) {
    if (msg.startsWith('INFO: '))
      return;
    let html = this.ansiUp.ansi_to_html(msg);
    let newElement = '<p id=t' + this.currentID + ' >' + html + '</p>';
    this.textIDs.push('t' + this.currentID);
    this.currentID++;

    let terminal = document.getElementById('terminal');
    if (terminal) {
      terminal.innerHTML += newElement;
      if (this.textIDs.length > 1000) {
        let id = this.textIDs.shift();
        let nodeToRemove = document.getElementById(id);
        if (nodeToRemove)
          nodeToRemove.parentNode.removeChild(nodeToRemove);
      }
      terminal.parentNode.scrollTop = terminal.parentNode.scrollHeight;
    }
  }

  createErrorMessage(msg) {
    if (msg.startsWith('WARNING: It is not recommended to run Webots as root.'))
      return;

    let newElement = '<p id=t' + this.currentID + ' style="color:red">' + msg + '</p>';
    this.textIDs.push('t' + this.currentID);
    this.currentID++;

    let terminal = document.getElementById('terminal');
    if (terminal) {
      terminal.innerHTML += newElement;
      if (this.textIDs.length > 1000) {
        let id = this.textIDs.shift();
        let nodeToRemove = document.getElementById(id);
        if (nodeToRemove)
          nodeToRemove.parentNode.removeChild(nodeToRemove);
      }
      terminal.parentNode.scrollTop = terminal.parentNode.scrollHeight;
    }
  }
}
