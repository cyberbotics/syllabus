export default class Terminal {
  constructor(parentNode) {
    this.ansiUp = new AnsiUp();
    this.text = '';

    document.addEventListener('keydown', e => {
      if (e.ctrlKey && e.code === 'KeyL') {
        e.preventDefault();
        this.text = '';
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
    this.text += html + '</br>';
    let terminal = document.getElementById('terminal');
    if (terminal)
      terminal.innerHTML = this.text + '</br>';
  }

  createErrorMessage(msg) {
    if (msg.startsWith('WARNING: It is not recommended to run Webots as root.'))
      return;

    this.text += '<span style="color:red">' + msg + '</span></br>';
    let terminal = document.getElementById('terminal');
    if (terminal)
      terminal.innerHTML = this.text + '</br>';
  }
}
