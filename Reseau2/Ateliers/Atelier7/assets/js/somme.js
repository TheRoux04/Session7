console.log("Coucou")
document.querySelector("button").addEventListener("click", () => {
    let nb1 = document.getElementById("nb1").value;
    let nb2 = document.getElementById("nb2").value;
    let resultat = Number(nb1) + Number(nb2);
    var newWindow = window.open();
    newWindow.document.write(resultat);
});