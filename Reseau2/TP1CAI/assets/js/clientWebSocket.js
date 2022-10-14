let ws = new WebSocket("ws://localhost:8080/wsClient");

let clientId = 0;

ws.onopen = function(evt) {
    clientId++;
    console.log("OPENCLIENT");
    ws.send("Client connected");
}

window.onbeforeunload = function() {
    ws.close();
}

ws.onclose = function(evt) {
    ws.send("Client disconnected:" + clientId);
    console.log("CLOSE");
}


ws.onmessage = function(evt) {
    let message = evt.data.split(":");
    console.log(message[0]);
    if (message[0] === "YOURID") {
        clientId = message[1];
        document.getElementById("clientId").value = message[1];
    }
    else if (evt.data === "Client connected") {

    }
    else if (evt.data === "Tech disconnected") {
        ws.close();
    }
    else {
        document.getElementById("message-container").insertAdjacentHTML("beforeend", "<p><b>Tech:</b>" + evt.data + "</p>");
    }
    return false;
}


document.getElementById("sendC").onclick = function(evt) {
    if (!ws) {
        return false;
    }

    ws.send(document.getElementById("message").value + ":" + clientId); // Envoi d'un message
    document.getElementById("message-container").insertAdjacentHTML("beforeend", "<p><b>Vous:</b>" + document.getElementById("message").value + "</p>");
    document.getElementById("message").value = "";
    return false;
};
