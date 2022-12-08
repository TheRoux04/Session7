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
		if s[1] == "10" {
			insertNewCooking(id, s[2])
		} else if s[1] == "200" {
			updateCooking(id, s[2])
		} else {
			updateCooling(id, s[2])
		}

	}
}

func openConnection() {
	var err error
	database, err = sql.Open("sqlite3", "./Database/TP2Boucherie.db")
	if err != nil {
		log.Fatal(err)
	}
}

func insertNewCooking(sondeID int, newCooking string) {
	fmt.Println("Insert")
	statement, err := database.Prepare("INSERT INTO SondesInfos (sondeId, newCooking) VALUES (?, ?)")
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println(err)
	_, err = statement.Exec(strconv.Itoa(sondeID), newCooking)

	if err != nil {
		//fmt.Println(err)
		return
	}
	fmt.Println(err)
}

func updateCooking(sondeID int, finishCooking string) {
	var exist int
	row := database.QueryRow("SELECT IIF(EXISTS (SELECT * FROM SondesInfos WHERE sondeId = ?), 1, 0)", strconv.Itoa(sondeID))
	err := row.Scan(&exist)
	if err != nil {
		return
	}
	if exist == 0 {
		statement, err := database.Prepare("UPDATE SondesInfos SET finishCooking = ? WHERE sondeId = ?")
		if err != nil {
			log.Fatal(err)
		}
		_, err = statement.Exec(finishCooking, strconv.Itoa(sondeID))
		if err != nil {
			return
		}
	}
}

func updateCooling(sondeID int, finishCooling string) {
	var exist int
	row := database.QueryRow("IF EXISTS (SELECT * FROM SondesInfos WHERE sondeId = ?) SELECT 1 ELSE SELECT 0", strconv.Itoa(sondeID))
	err := row.Scan(&exist)
	if err != nil {
		return
	}
	if exist == 0 {
		statement, err := database.Prepare("UPDATE SondesInfos SET finishCooling = ? WHERE sondeId = ?")
		if err != nil {
			log.Fatal(err)
		}
		_, err = statement.Exec(finishCooling, strconv.Itoa(sondeID))
		if err != nil {
			return
		}
	}
}
