package main

import (
	"github.com/gorilla/websocket"
	"io"
	"log"
	"net/http"
	"os"
	"userRepository"
)

var upgrader = websocket.Upgrader{}

func main() {

	http.HandleFunc("/home", home)
	http.HandleFunc("/client", client)
	http.HandleFunc("/tech", tech)
	http.HandleFunc("/error404", error404)
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

func home(w http.ResponseWriter, r *http.Request) {

	switch r.Method {
	case "GET":
		vueRaw, _ := os.ReadFile("./views/home.html")
		vue := string(vueRaw)
		w.Header().Set("Content-Type", "text/html")
		io.WriteString(w, vue)
	case "POST":
		r.ParseForm()
		username := r.FormValue("username")
		password := r.FormValue("password")

		if username != "" || password != "" {
			userRepository.getUser(username, password)

		}

		http.Redirect(w, r, "/tech", http.StatusTemporaryRedirect)
	}
}

func client(w http.ResponseWriter, r *http.Request) {
	vueRaw, _ := os.ReadFile("./views/client.html")
	vue := string(vueRaw)

	w.Header().Set("Content-Type", "text/html")
	io.WriteString(w, vue)
}

func tech(w http.ResponseWriter, r *http.Request) {
	vueRaw, _ := os.ReadFile("./views/tech.html")
	vue := string(vueRaw)

	w.Header().Set("Content-Type", "text/html")
	io.WriteString(w, vue)
}

func error404(w http.ResponseWriter, r *http.Request) {
	vueRaw, _ := os.ReadFile("./views/404.html")
	vue := string(vueRaw)

	w.Header().Set("Content-Type", "text/html")
	io.WriteString(w, vue)

}

func login(username string, password string) {

}
