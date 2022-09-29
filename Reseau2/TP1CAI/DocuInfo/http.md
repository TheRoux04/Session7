# Http

## Serveur Web

Si vous avez besoin d'un serveur web, vous pouvez facilement vous en créez un en utilisant l'utilitaire suivant:

```go
package main
import (
  "fmt"
  "net/http"
)

func main() {
  http.HandleFunc("/", gererConnection) 
  http.ListenAndServe(":8080", nil) 
} 
  
func gererConnection(w http.ResponseWriter, r *http.Request) {
  w.Header().Set("Content-Type", "text/html",)
  io.WriteString(w, `<html>
                     <head>
                     <meta charset="UTF-8">
                     <title>Hello, World</title>
                     </head>
                     <body> 
                     </body>
                     </html>`,)
}
```

Ceci va créer un serveur web écoutant sur le port 80 qui a chaque requête retourne une page vide.

Il aurait été possible de supporter plusieurs URL différentes en utilisant cette description plus précise par route:

```go
http.HandleFunc("/hello", hello)
http.HandleFunc("/headers", headers)
```

Ceci aurait créé deux sections dans le sites web: /hello et /headers, chacun étant répondu par un service différent.

Il aurait aussi été possible de lui donner un répertoire static qui ne sera pas répondu par des fonctions:

```go
fileServer := http.FileServer(http.Dir("./static"))
http.Handle("/assets", fileserver)
```

## Recevoir du POST

Pour recevoir du POST il faut simplement:

```go
r.ParseForm()
r.Form.Get("nomDeMonInput")
```

Si vous faites une API, vous pouvez accéder au contenu via `r.Body`.

## Redirection

Pour rediriger vers une autre page HTML, utilisez la fonction suivante:

```go
http.Redirect(w, r, "/404", http.StatusTemporaryRedirect)
```

## Cookies

Pour écrire un cookie:

```go
var sessionCookie http.Cookie = http.Cookie{Name: "session", Value: sessionKey, HttpOnly: true}
http.SetCookie(w, &sessionCookie)
```

Pour lire un cookie:

```go
cookie, cookieError := r.Cookie("session")
```

## Websocket

WebSocket est un standard du Web désignant un protocole réseau de la couche application et une interface de programmation du World Wide Web visant à créer des canaux de communication full-duplex par-dessus une connexion TCP pour les navigateurs web. Le protocole a été normalisé par l'IETF dans la RFC 6455 en 2011 et l'interface de programmation par le W3C. 

Il permet à une application à communiquer en permanence avec un serveur et de pouvoir recevoir des mises à jours provenant du serveur sans questionner le serveur à chaque tant de temps.

Le web est de façon général a toujours été unidirectionnel: c'est à dire qu'un client demande une information à un serveur une information et le serveur lui rend. Si l'information doit être mise à jour, la requête doit revenir du client, il n'y a pas de possibilité au serveur de communiquer simplement une mise à jour vers le client.

La mise en place d'un serveur websocket n'est pas bien prise en charge par les outils par défaut de golang. Il est fortement suggéré d'utiliser cette source:  https://github.com/gorilla/websocket:

Le code suivant est disponible ici: 
https://github.com/gorilla/websocket/blob/master/examples/echo/server.go

```go
var upgrader = websocket.Upgrader{} // use default options

func echo(w http.ResponseWriter, r *http.Request) {
	c, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Print("upgrade:", err)
		return
	}
	defer c.Close()
	for {
		mt, message, err := c.ReadMessage()
		if err != nil {
			log.Println("read:", err)
			break
		}
		log.Printf("recv: %s", message)
		err = c.WriteMessage(mt, message)
		if err != nil {
			log.Println("write:", err)
			break
		}
	}
}
```

Création du socket qui transforme une réponse http en socket ouvert qui fera que chaque message reçu dans ce socket se retrouvera dans la boucle for. Dans le code ci-dessous, c'est simplement affichage dans le prompt. Si vous testez le code localement, vous allez remarquer que le message est un tableau de byte donc vous pouvez y stocker ce que vous souhaitez (string ou autres). 

Plus tard, dans le code, nous voyons l'assignation suivante dans la boucle main:

```go
func main() {
	flag.Parse()
	log.SetFlags(0)
	http.HandleFunc("/echo", echo)
	http.HandleFunc("/", home)
	log.Fatal(http.ListenAndServe(*addr, nil))
}
```

Chaque requête faîte sur l'URL echo se retrouve sur le channel websocket directement. Il faut cependant qu'elle soit formattée correctement de la part de javaScript:

```js
document.getElementById("open").onclick = function(evt) {
  if (ws) {
     return false;
  }
  ws = new WebSocket("{{.}}"); // Création du socket
  ws.onopen = function(evt) {
    print("OPEN");
  }
  ws.onclose = function(evt) {
    print("CLOSE");
    ws = null; // Fermeture du socket
  }
  ws.onmessage = function(evt) {
    print("RESPONSE: " + evt.data); // Lorsqu'on reçoit un message
  }
  ws.onerror = function(evt) {
    print("ERROR: " + evt.data);
  }
  return false;
};
  
document.getElementById("send").onclick = function(evt) {
  if (!ws) {
    return false;
  }
  print("SEND: " + input.value);
  ws.send(input.value); // Envoi d'un message
  return false;
};

document.getElementById("close").onclick = function(evt) {
  if (!ws) {
    return false;
  }
  ws.close();
  return false;
};
```