const connectButton = document.getElementById ('connect-button');
let port;

if ('serial' in navigator) {
  connectButton.addEventListener('click', function () {
    if (port) {
      port.close();
      port = undefined;
      connectButton.innerText = '🔌 Connect';
    }
    else {
      getReader();
    }
  });

  connectButton.disabled = false;
}

