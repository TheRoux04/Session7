let ws = new WebSocket("ws://localhost:8080/ws");
ws.onmessage = evt => {
    console.log(evt.data);
}
document.querySelector("button").addEventListener("click", () => {
    let nb1 = document.getElementById("nb1").value;
    let nb2 = document.getElementById("nb2").value;
    let resultat = Number(nb1) + Number(nb2);
    ws.send(resultat)
    var newWindow = window.open();
    newWindow.document.write(resultat);
});