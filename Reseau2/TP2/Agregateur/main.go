package main

import (
	"database/sql"
	"fmt"
	_ "github.com/mattn/go-sqlite3"
	"github.com/pion/dtls/v2"
	"log"
	"net"
	"strconv"
	"strings"
)

var database *sql.DB

func main() {
	openConnection()
	config := &dtls.Config{
		InsecureSkipVerify: true,
	}
	conn, err := dtls.Dial("udp", &net.UDPAddr{Port: 8000}, config)
	if err != nil {
		log.Fatal(err)
	}
	for {
		var buffer = make([]byte, 256)
		_, err := conn.Read(buffer)
		if err != nil {
			return
		}
		//fmt.Println(string(buffer))
		s := strings.Split(string(buffer), "/")
		id, err := strconv.Atoi(s[0])
		if err != nil {
			log.Fatal(err)
		}
		fmt.Println(s[0])
		fmt.Println(s[1])
		fmt.Println(s[2])
		if s[1] == "Start" {
			insertNewCooking(id, s[2])
		} else if s[1] == "Cooked" {
			updateCooking(id, s[2])
		} else {
			updateCooling(id, s[2])
		}

	}
}

func openConnection() {
	var err error
	database, err = sql.Open("sqlite3", "Database/TP2Boucherie.db")
	if err != nil {
		log.Fatal(err)
	}
}

func insertNewCooking(sondeID int, newCooking string) {
	fmt.Println("Insert")
	statement, err := database.Prepare("INSERT INTO SondeInfos (sondeId, newCooking) VALUES (?, ?)")
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println(err)
	_, err = statement.Exec(sondeID, newCooking)
	if err != nil {
		return
	}
}

func updateCooking(sondeID int, finishCooking string) {
	var exist int
	row := database.QueryRow("IF EXISTS (SELECT * FROM SondeInfos WHERE sondeId = ?) SELECT 1 ELSE SELECT 0", sondeID)
	err := row.Scan(&exist)
	if err != nil {
		return
	}
	if exist == 0 {
		statement, err := database.Prepare("UPDATE SondeInfos SET finishCooking = ? WHERE sondeId = ?")
		if err != nil {
			log.Fatal(err)
		}
		_, err = statement.Exec(finishCooking, sondeID)
		if err != nil {
			return
		}
	}
}

func updateCooling(sondeID int, finishCooling string) {
	var exist int
	row := database.QueryRow("IF EXISTS (SELECT * FROM SondeInfos WHERE sondeId = ?) SELECT 1 ELSE SELECT 0", sondeID)
	err := row.Scan(&exist)
	if err != nil {
		return
	}
	if exist == 0 {
		statement, err := database.Prepare("UPDATE SondeInfos SET finishCooling = ? WHERE sondeId = ?")
		if err != nil {
			log.Fatal(err)
		}
		_, err = statement.Exec(finishCooling, sondeID)
		if err != nil {
			return
		}
	}
}
