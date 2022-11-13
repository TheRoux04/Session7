package main

import (
	"github.com/gorilla/websocket"
	"io"
	"log"
	"net/http"
	"os"
	"strings"
)

var upgrader = websocket.Upgrader{}

func main() {
	http.HandleFunc("/", gererConnection)
	http.HandleFunc("/ws", ws)

	fileServer := http.FileServer(http.Dir("./assets"))
	http.Handle("/assets/", http.StripPrefix("/assets/", fileServer))

	http.ListenAndServe(":8080", nil)
}

func ws(w http.ResponseWriter, r *http.Request) {
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

func gererConnection(w http.ResponseWriter, r *http.Request) {
	vueRaw, _ := os.ReadFile("./views/index2.html")
	vue := string(vueRaw)
	vue = strings.Replace(vue, "###TITRE###", "Blearg", 1)

	w.Header().Set("Content-Type", "text/html")
	io.WriteString(w, vue)
}
