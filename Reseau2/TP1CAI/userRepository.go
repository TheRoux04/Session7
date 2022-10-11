package main

import (
	"database/sql"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

var database *sql.DB

func openConnection() {
	var err error
	database, err = sql.Open("sqlite3", "Database/BDCAI.db")
	if err != nil {
		log.Fatal(err)
	}
}

func insertTech(username string, password string) {
	statement, err := database.Prepare("INSERT INTO Techniciens (username, password) VALUES (?, ?)")
	if err != nil {
		log.Fatal(err)
	}
	statement.Exec(username, password)
}

func updateTech(id string, username string, password string) {
	statement, err := database.Prepare("UPDATE Techniciens SET username = ?, password = ? WHERE techID = ?")
	if err != nil {
		log.Fatal(err)
	}
	statement.Exec(username, password, id)
}

func delTech(id string) {
	statement, err := database.Prepare("DELETE FROM Techniciens WHERE techID = ?")
	if err != nil {
		log.Fatal(err)
	}
	statement.Exec(id)
}

func getUser(username string) (int, string, int) {
	var id int
	var password string
	var isAdmin int
	database.QueryRow("SELECT techID, password, isAdmin FROM Techniciens WHERE username = ?", username).Scan(&id, &password, &isAdmin)
	return id, password, isAdmin
}

func getAllTech() []string {
	var techs []string
	rows, err := database.Query("SELECT techId, username FROM Techniciens WHERE isAdmin = 0")
	if err != nil {
		log.Fatal(err)
	}
	defer rows.Close()
	for rows.Next() {
		var id string
		var username string
		rows.Scan(&id, &username)
		techs = append(techs, id+":"+username)
	}
	return techs
}

func setToken(id int, token string) {
	statement, err := database.Prepare("UPDATE Techniciens SET token = ? WHERE techID = ?")
	if err != nil {
		log.Fatal(err)
	}
	statement.Exec(token, id)
}

func unsetToken(token string) {
	statement, err := database.Prepare("UPDATE Techniciens SET token = NULL WHERE token = ?")
	if err != nil {
		log.Fatal(err)
	}
	statement.Exec(token)
}

func getToken(username string) string {
	var token string
	database.QueryRow("SELECT token FROM Techniciens WHERE username = ?", username).Scan(&token)
	return token
}

func checkNoTokenTech() bool {
	var token int
	row := database.QueryRow("SELECT COUNT(techID) FROM Techniciens WHERE isAdmin = 0 AND token IS NOT NULL")
	row.Scan(&token)
	return token == 0
}

func getWhoConnected(token string) int {
	var isAdmin int
	row := database.QueryRow("SELECT isAdmin FROM Techniciens WHERE token = ?", token)
	row.Scan(&isAdmin)
	return isAdmin
}
