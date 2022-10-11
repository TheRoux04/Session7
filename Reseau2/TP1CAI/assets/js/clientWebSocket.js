let ws = new WebSocket("ws://localhost:8080/wsClient");

ws.onopen = function(evt) {
    console.log("OPENCLIENT");
    ws.send("Client connected");
}


ws.onmessage = function(evt) {
    document.getElementById("message-container").insertAdjacentHTML("beforeend", "<p><b>Tech</b>:" + evt.data + "</p>");
    return false;
}



document.getElementById("sendC").onclick = function(evt) {
    if (!ws) {
        return false;
    }

    ws.send(document.getElementById("message").value); // Envoi d'un message
    document.getElementById("message-container").insertAdjacentHTML("beforeend", "<p><b>Vous</b>:" + document.getElementById("message").value + "</p>");
    document.getElementById("message").value = "";
    return false;
};
