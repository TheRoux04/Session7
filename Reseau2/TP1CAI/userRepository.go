package main

import (
	"database/sql"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

var database *sql.DB

func openConnection() {
	var err error
	database, err = sql.Open("sqlite3", "./Database/BDCAI.db")
	if err != nil {
		log.Fatal(err)
	}
}

type Login struct {
	Username string `json:"username"`
	Password string `json:"password"`
}

func insertUser(username string, password string) {
	statement, _ := database.Prepare("INSERT INTO Techniciens (username, password) VALUES (?, ?)")
	statement.Exec(username, password)
}

func getUser(username string) (int, string) {
	var id int
	var password string
	row := database.QueryRow("SELECT techID, password FROM Techniciens WHERE username = ?", username)
	row.Scan(&password)
	return id, password
}

func setToken(id int, token string) {
	statement, err := database.Prepare("UPDATE Techniciens SET token = ? WHERE techID = ?")
	if err != nil {
		log.Fatal(err)
	}
	statement.Exec(token, id)
}

func unsetToken() {
	statement, err := database.Prepare("UPDATE Techniciens SET token = NULL WHERE token IS NOT NULL")
	if err != nil {
		log.Fatal(err)
	}
	statement.Exec()
}

func getToken(username string) string {
	var token string
	row := database.QueryRow("SELECT token FROM Techniciens WHERE username = ?", username)
	row.Scan(&token)
	return token
}

func checkNoToken() bool {
	var token int
	row := database.QueryRow("SELECT COUNT(techID) FROM Techniciens WHERE token IS NOT NULL")
	row.Scan(&token)
	return token == 0
}

/*
func userExists(username string) bool {

}
*/
