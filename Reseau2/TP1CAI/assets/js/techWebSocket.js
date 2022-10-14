let ws = new WebSocket("ws://localhost:8080/wsTech");
let stringBtnClient;
let nbOnline = 0;
let currentClient = 0;

let chats = [];


let someChat = chats.find(chat => chat.id === currentClient);

ws.onopen = function(evt) {
    console.log("OPENTECH");
}

window.onbeforeunload = function() {
    ws.close();
}

ws.onclose = function(evt) {
    ws.send("Tech disconnected");
    console.log("CLOSE");
}

ws.onmessage = function(evt) {
    let message = evt.data.split(":");
    console.log(message);
    if (message[0] === "Client connected") {
        nbOnline++;

        const button = document.createElement("button");
        button.classList.add("btn");
        button.classList.add("btn-primary");
        button.id = "client" + message[1];
        button.innerHTML = nbOnline.toString();
        button.addEventListener("click", () => {
            changeClient(message[1]);
        });

        console.log("Nouveau button");
        document.getElementById("client-container").appendChild(button);
        document.getElementById("client-container").insertAdjacentHTML("beforeend", "<br>");
        document.getElementById("client-container").insertAdjacentHTML("beforeend", "<br>");

        let newChatroom = {
            id: message[1],
            messages: []
        }
        chats.push(newChatroom);

        ws.send("YOURID:" + nbOnline);
    }
    else if (message[0] === "Client disconnected") {
        chats = chats.filter(chat => chat.id !== message[1]);
        nbOnline--;
        document.getElementById("client-container").innerHTML = '';
        document.getElementById("")
        for (let i = 0; i < nbOnline; i++) {
            document.getElementById("client-container").insertAdjacentHTML("beforeend", "<button class=\"btn btn-primary\" id=\"client" + i + "\">" + i + "</button>");
        }
    }
    else{
        chats[currentClient].messages.push("Client:" + message[0]);
        document.getElementById("message-container").insertAdjacentHTML("beforeend", "<b>Client:</b>" + message[0]);
    }

    return false;
}

document.getElementById("sendT").onclick = function(evt) {
    evt.preventDefault()
    if (!ws) {
        return false;
    }
    console.log(document.getElementById("message").value + ":" + currentClient);
    console.log(currentClient);

    ws.send(document.getElementById("message").value + ":" + currentClient); // Envoi d'un message
    chats[currentClient].messages.push("Tech:" + document.getElementById("message").value);
    document.getElementById("message-container").insertAdjacentHTML("beforeend", "<p><b>Tech:</b>" + document.getElementById("message").value + "</p>");
    document.getElementById("message").value = "";
    return false;

};

function changeClient(id) {
    console.log("Change client");
    currentClient = id;
    document.getElementById("message-container").innerHTML = '';
    chats[currentClient].messages.forEach(message => {
        document.getElementById("message-container").insertAdjacentHTML("beforeend", "<p>" + message + "</p>");
    });
}

