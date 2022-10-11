package repositories

import (
	"database/sql"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

var database *sql.DB

func openConnection() {
	var err error
	database, err = sql.Open("sqlite3", "./chat.db")
	if err != nil {
		log.Fatal(err)
	}
}

type Login struct {
	Username string `json:"username"`
	Password string `json:"password"`
}

func insertUser(username string, password string) {
	statement, _ := database.Prepare("INSERT INTO Users (username, password) VALUES (?, ?)")
	statement.Exec(username, password)
}

func getUser(username string) (string, string) {
	var password string
	row := database.QueryRow("SELECT password FROM Users WHERE username = ?", username)
	row.Scan(&password)
	return username, password
}

func userExists(username string) bool {

}
