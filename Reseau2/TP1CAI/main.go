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
	"strings"
	"time"
)

var upgrader = websocket.Upgrader{}

func main() {
	openConnection()
	http.HandleFunc("/", home)
	http.HandleFunc("/client", client)
	http.HandleFunc("/tech", tech)
	http.HandleFunc("/error404", error404)
	http.HandleFunc("/logout", logout)
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
	vueRaw, _ := os.ReadFile("./views/home.html")
	vue := string(vueRaw)
	w.Header().Set("Content-Type", "text/html")
	switch r.Method {
	case "GET":
		vue = strings.Replace(vue, "###ALERTHOME###", "", 1)
		if checkNoToken() == false {
			vue = strings.Replace(vue, "###SERVICESAVAILABLE###", "<button class='btn btn-danger' id='button_offline' disabled>Service hors ligne</button>", 1)
		} else {
			vue = strings.Replace(vue, "###SERVICESAVAILABLE###", "<button class='btn btn-success' id='button_online' >Service en ligne</button>", 1)
			log.Println("Tech cennecter")
		}
	case "POST":
		r.ParseForm()
		username := r.FormValue("username")
		password := r.FormValue("password")
		if checkNoToken() == true {
			if username != "" || password != "" {
				id, pass := getUser(username)
				if pass == password {
					log.Println("Connexion réussie")
					token := generateToken(username)
					cookie := http.Cookie{
						Name:  "tokenSession",
						Value: token,
					}
					http.SetCookie(w, &cookie)
					setToken(id, token)
					vue = strings.Replace(vue, "###SERVICESAVAILABLE###", "<button class='btn btn-success' id='button_online' >Service en ligne</button>", 1)

					http.Redirect(w, r, "/tech", http.StatusTemporaryRedirect)
				} else {
					vue = strings.Replace(vue, "###ALERTHOME###", "<div class='alert alert-danger'>Erreur de connection</div>", 1)
				}
			} else {
				vue = strings.Replace(vue, "###ALERTHOME###", "<div class='alert alert-danger'>Erreur de connection</div>", 1)
			}
		} else {
			vue = strings.Replace(vue, "###ALERTHOME###", "<div class='alert alert-danger'>Un technicien est déja connecté! Reessayer plus tard</div>", 1)
		}
	}

	io.WriteString(w, vue)
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

func logout(w http.ResponseWriter, r *http.Request) {
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

func deleteCookieHandler(rw http.ResponseWriter, r *http.Request) {

	c, err := r.Cookie("storage")
	if err != nil {
		panic(err.Error())
	}
	c.Name = "Deleted"
	c.Value = "Unuse"
	c.Expires = time.Unix(1414414788, 1414414788000)
}

//func modifyTech
