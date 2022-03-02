export default class Terminal {
  constructor(parentNode){
    this.ansiUp = new AnsiUp();
    this.text = '';
  }

  createMessage(msg) {
    let html = this.ansiUp.ansi_to_html(msg);
    console.log(html)
    this.text += html + '</br>';
    let terminal = document.getElementById('terminal');
    if (terminal)
      terminal.innerHTML = this.text + '</br>';
  }

  createErrorMessage(msg) {
    this.text += '<span style="color:red">' + msg + '</span></br>'
    let terminal = document.getElementById('terminal');
    if (terminal)
      terminal.innerHTML = this.text + '</br>';
  }
}
