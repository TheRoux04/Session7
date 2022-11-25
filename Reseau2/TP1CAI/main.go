package main

import (
	"encoding/base64"
	"github.com/gorilla/websocket"
	"golang.org/x/crypto/bcrypt"
	"io"
	"log"
	"math/rand"
	"net/http"
	"os"
	"strconv"
	"strings"
	"time"
)

var upgrader = websocket.Upgrader{}

func main() {
	clientsChan := map[int]chan []byte{}
	techChan := make(chan []byte)
	nbConnections := 1
	openConnection()
	http.HandleFunc("/", home)
	http.HandleFunc("/client", func(w http.ResponseWriter, r *http.Request) {
		client(clientsChan, techChan, w, r, nbConnections)
	})
	http.HandleFunc("/tech", tech)
	http.HandleFunc("/admin", adminMenu)
	http.HandleFunc("/allTech", allTech)
	http.HandleFunc("/ajout", addTech)
	http.HandleFunc("/edit", editTech)
	http.HandleFunc("/delete", deleteTech)
	http.HandleFunc("/error404", error404)
	http.HandleFunc("/logout", logout)
	http.HandleFunc("connecxionLog", connexionLog)
	http.HandleFunc("/wsClient", func(w http.ResponseWriter, r *http.Request) {
		wsClient(clientsChan, techChan, w, r, nbConnections)
	})
	http.HandleFunc("/wsTech", func(w http.ResponseWriter, r *http.Request) {
		wsTech(clientsChan, techChan, w, r)
	})

	fileServer := http.FileServer(http.Dir("./assets"))
	http.Handle("/assets/", http.StripPrefix("/assets/", fileServer))

	http.ListenAndServe(":8080", nil)
}

func wsClient(clientsChan map[int]chan []byte, techChan chan []byte, w http.ResponseWriter, r *http.Request, clientId int) {
	c, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Println("Error", err)
		return
	}
	defer c.Close()
	log.Println("wsClient")
	go sendMessageClient(c, techChan, clientId)
	client := clientsChan[clientId]
	clientId++
	for {
		msg := <-client
		c.WriteMessage(websocket.TextMessage, msg)
		log.Println("Le client a reçu le message")
	}
}

func sendMessageClient(c *websocket.Conn, techChan chan []byte, clientId int) {
	for {
		log.Println("msgClient")
		_, message, err := c.ReadMessage()
		if err != nil {
			log.Println("Client disconnected")
			techChan <- []byte("Client disconnected:" + strconv.Itoa(clientId))
			break
		}
		techChan <- message
	}
}

func wsTech(clientsChan map[int]chan []byte, techChan chan []byte, w http.ResponseWriter, r *http.Request) {
	c, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		return
	}
	defer c.Close()
	log.Println("wsTech")
	go sendMessageTech(c, clientsChan)
	for {
		msg := <-techChan
		log.Println(string(msg))
		c.WriteMessage(websocket.TextMessage, msg)
		log.Println("Le tech a reçu le message")
	}
}

func sendMessageTech(c *websocket.Conn, clientsChan map[int]chan []byte) {
	for {
		log.Println("msgTech")
		_, message, err := c.ReadMessage()
		if err != nil {
			log.Println("Tech disconnected")
			for _, client := range clientsChan {
				client <- []byte("Tech disconnected")
				close(client)
			}
			break
		}
		messageComponents := strings.Split(string(message), ":")
		value, _ := strconv.Atoi(messageComponents[1])
		if messageComponents[0] == "Client disconnected" {
			close(clientsChan[value])
		}
		clientsChan[value] <- message
	}
}

func home(w http.ResponseWriter, r *http.Request) {
	vueRaw, _ := os.ReadFile("./views/home.html")
	vue := string(vueRaw)
	w.Header().Set("Content-Type", "text/html")
	theCookie, err := r.Cookie("tokenSession")
	if err != nil {
		switch r.Method {
		case "GET":
			vue = strings.Replace(vue, "###ALERTHOME###", "", 1)
			if checkNoTokenTech() == true {
				vue = strings.Replace(vue, "###SERVICESAVAILABLE###", "<button class='btn btn-danger' id='button_offline' disabled>Service hors ligne</button>", 1)
			} else {
				vue = strings.Replace(vue, "###SERVICESAVAILABLE###", "<a class=\"btn btn-primary \" id=\"button_online\" href=\"/client\">Service en ligne</a>", 1)
				log.Println("Tech connecter")
			}
		case "POST":
			r.ParseForm()
			username := r.FormValue("username")
			password := r.FormValue("password")
			if username != "" || password != "" {
				canConnect := false
				id, pass, isAdmin := getUser(username)
				if isAdmin == 0 {
					if checkNoTokenTech() == true {
						canConnect = true
					} else {
						vue = strings.Replace(vue, "###ALERTHOME###", "<div class='alert alert-danger'>Un technicien est déja connecté! Reessayer plus tard</div>", 1)
						vue = strings.Replace(vue, "###SERVICESAVAILABLE###", "<a class=\"btn btn-primary \" id=\"button_online\" href=\"/client\">Service en ligne</a>", 1)

					}
				} else {
					canConnect = true
				}

				if canConnect {
					if pass == password {
						log.Println("Connexion réussie")
						token := generateToken(username)
						cookie := http.Cookie{
							Name:  "tokenSession",
							Value: token,
						}
						http.SetCookie(w, &cookie)
						setToken(id, token)
						if isAdmin == 0 {
							http.Redirect(w, r, "/tech", http.StatusTemporaryRedirect)
						} else {
							http.Redirect(w, r, "/admin", http.StatusTemporaryRedirect)
						}
					} else {
						vue = strings.Replace(vue, "###ALERTHOME###", "<div class='alert alert-danger'>Erreur de connection</div>", 1)
					}
				}
			} else {
				vue = strings.Replace(vue, "###ALERTHOME###", "<div class='alert alert-danger'>Erreur de connection</div>", 1)
			}
		}
	} else {
		who := whoConnected(theCookie.Value)
		if who == 0 {
			http.Redirect(w, r, "/tech", http.StatusTemporaryRedirect)
		} else {
			http.Redirect(w, r, "/admin", http.StatusTemporaryRedirect)
		}
	}

	io.WriteString(w, vue)
}

func whoConnected(token string) int {
	whoConnected := getWhoConnected(token)
	return whoConnected
}

func client(clientsChan map[int]chan []byte, techChan chan []byte, w http.ResponseWriter, r *http.Request, clientId int) {
	vueRaw, _ := os.ReadFile("./views/client.html")
	vue := string(vueRaw)
	w.Header().Set("Content-Type", "text/html")

	if techChan == nil {
		http.Redirect(w, r, "/", http.StatusTemporaryRedirect)
	}

	clientChan := make(chan []byte)
	clientsChan[clientId] = clientChan
	vue = strings.Replace(vue, "###CLIENTID###", strconv.Itoa(clientId), 1)
	clientId++

	io.WriteString(w, vue)
}

func tech(w http.ResponseWriter, r *http.Request) {
	vueRaw, _ := os.ReadFile("./views/tech.html")
	vue := string(vueRaw)
	w.Header().Set("Content-Type", "text/html")

	theCookie, err := r.Cookie("tokenSession")
	if err != nil {
		log.Fatal(err)
	}
	if whoConnected(theCookie.Value) == 1 {
		http.Redirect(w, r, "/", http.StatusTemporaryRedirect)
	}

	io.WriteString(w, vue)
}

func adminMenu(w http.ResponseWriter, r *http.Request) {
	vueRaw, _ := os.ReadFile("./views/adminMenu.html")
	vue := string(vueRaw)
	w.Header().Set("Content-Type", "text/html")

	theCookie, err := r.Cookie("tokenSession")
	if err != nil {
		log.Fatal(err)
	}
	if whoConnected(theCookie.Value) == 0 {
		http.Redirect(w, r, "/", http.StatusTemporaryRedirect)
	}

	io.WriteString(w, vue)
}

func allTech(w http.ResponseWriter, r *http.Request) {
	vueRaw, _ := os.ReadFile("./views/allTech.html")
	vue := string(vueRaw)
	w.Header().Set("Content-Type", "text/html")

	theCookie, err := r.Cookie("tokenSession")
	if err != nil {
		log.Fatal(err)
	}
	if whoConnected(theCookie.Value) == 0 {
		http.Redirect(w, r, "/", http.StatusTemporaryRedirect)
	}

	var bigString string

	allTech := getAllTech()
	for _, tech := range allTech {
		oneTech := strings.Split(tech, ":")
		bigString += "<li class=\"list-group-item d-flex\">\n    " +
			"			<span class=\"flex-grow-1 my-auto\">{{TECH}}</span>\n    " +
			"				<a class=\"btn btn-primary mx-1 rounded-1\" href=\"./edit?techId={{ID}}\">\n      " +
			"				Modifier\n    " +
			"				</a>\n    " +
			"				<a class=\"btn btn-danger mx-1 rounded-1\" href=\"./delete?techId={{ID}}\" >\n      " +
			"				Supprimer\n    " +
			"				</a>\n  " +
			"		</li>"
		bigString = strings.Replace(bigString, "{{TECH}}", oneTech[1], 1)
		bigString = strings.Replace(bigString, "{{ID}}", oneTech[0], 2)
	}

	vue = strings.Replace(vue, "###TECHNICIENS###", bigString, 1)

	io.WriteString(w, vue)
}

func addTech(w http.ResponseWriter, r *http.Request) {
	vueRaw, _ := os.ReadFile("./views/addTech.html")
	vue := string(vueRaw)
	w.Header().Set("Content-Type", "text/html")

	theCookie, err := r.Cookie("tokenSession")
	if err != nil {
		log.Fatal(err)
	}
	if whoConnected(theCookie.Value) == 0 {
		http.Redirect(w, r, "/", http.StatusTemporaryRedirect)
	}

	switch r.Method {
	case "POST":
		r.ParseForm()
		username := r.FormValue("username")
		password := r.FormValue("password")
		if username != "" || password != "" {
			insertTech(username, password)
			http.Redirect(w, r, "/allTech", http.StatusTemporaryRedirect)
		}
	}

	io.WriteString(w, vue)
}

func editTech(w http.ResponseWriter, r *http.Request) {
	vueRaw, _ := os.ReadFile("./views/editTech.html")
	vue := string(vueRaw)
	w.Header().Set("Content-Type", "text/html")

	theCookie, err := r.Cookie("tokenSession")
	if err != nil {
		log.Fatal(err)
	}
	if whoConnected(theCookie.Value) == 0 {
		http.Redirect(w, r, "/", http.StatusTemporaryRedirect)
	}

	switch r.Method {
	case "POST":
		r.ParseForm()
		values := r.URL.Query()
		techId := values.Get("techId")
		username := r.FormValue("username")
		password := r.FormValue("password")
		if username != "" || password != "" {
			updateTech(techId, username, password)
			http.Redirect(w, r, "/allTech", http.StatusTemporaryRedirect)
		}
	}

	io.WriteString(w, vue)
}

func deleteTech(w http.ResponseWriter, r *http.Request) {
	theCookie, err := r.Cookie("tokenSession")
	if err != nil {
		log.Fatal(err)
	}
	if whoConnected(theCookie.Value) == 0 {
		http.Redirect(w, r, "/", http.StatusTemporaryRedirect)
	}

	switch r.Method {
	case "GET":
		values := r.URL.Query()
		techId := values.Get("techId")
		delTech(techId)
		http.Redirect(w, r, "/allTech", http.StatusTemporaryRedirect)
	}
}

func error404(w http.ResponseWriter, r *http.Request) {
	vueRaw, _ := os.ReadFile("./views/404.html")
	vue := string(vueRaw)
	w.Header().Set("Content-Type", "text/html")

	io.WriteString(w, vue)
}

func logout(w http.ResponseWriter, r *http.Request) {
	theCookie, err := r.Cookie("tokenSession")
	if err != nil {
		log.Fatal(err)
	}
	unsetToken(theCookie.Value)
	c := &http.Cookie{
		Name:     "tokenSession",
		Value:    "",
		Path:     "/",
		Expires:  time.Unix(0, 0),
		HttpOnly: true,
	}
	http.SetCookie(w, c)

	http.Redirect(w, r, "/", http.StatusTemporaryRedirect)
}

// GenerateToken returns a unique token based on the provided email string
func generateToken(username string) string {
	rand.Seed(time.Now().UnixNano())
	username = username + string(rand.Intn(1000))
	hash, err := bcrypt.GenerateFromPassword([]byte(username), bcrypt.DefaultCost)
	if err != nil {
		log.Fatal(err)
	}
	return base64.StdEncoding.EncodeToString(hash)
}

func connexionLog(w http.ResponseWriter, r *http.Request) {
	vueRaw, _ := os.ReadFile("./views/connexionLog.html")
	vue := string(vueRaw)
	w.Header().Set("Content-Type", "text/html")

	theCookie, err := r.Cookie("tokenSession")
	if err != nil {
		log.Fatal(err)
	}
	if whoConnected(theCookie.Value) == 0 {
		//http.Redirect(w, r, "/", http.StatusTemporaryRedirect)
	}

	io.WriteString(w, vue)
}
