let ws = new WebSocket("ws://localhost:8080/wsTech");
let allClients = [];

ws.onopen = function(evt) {
    console.log("OPENTECH");
}

ws.onmessage = function(evt) {
    if (evt.data.includes("Client connected")) {

    }
    document.getElementById("message-container").insertAdjacentHTML("beforeend", "<p><b>Client:</b>:" + evt.data + "</p>");
    return false;
}

document.getElementById("sendT").onclick = function(evt) {
    evt.preventDefault()
    if (!ws) {
        return false;
    }
    console.log(evt.data);
    ws.send(document.getElementById("message").value); // Envoi d'un message
    document.getElementById("message-container").insertAdjacentHTML("beforeend", "<p><b>Vous</b>:" + document.getElementById("message").value + "</p>");
    document.getElementById("message").value = "";
    return false;
};
