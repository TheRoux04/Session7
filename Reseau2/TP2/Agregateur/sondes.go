package main

import (
	"database/sql"
	"fmt"
	"github.com/pion/dtls/v2"
	"log"
	"net"
	"strconv"
	"strings"
)

func sondes(database *sql.DB) {
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
		s := strings.Split(string(buffer), "/")
		id, err := strconv.Atoi(s[0])
		if err != nil {
			log.Fatal(err)
		}
		fmt.Println(s[0])
		fmt.Println(s[1])
		fmt.Println(s[2])
		fmt.Println(s[3])
		if s[1] >= "20" && s[2] == "" {
			println("Start cooking")
			insertNewCooking(id, s[2], database)
		} else if s[1] >= "200" && s[2] == "Cooking" {
			println("Finish cooking")
			updateCooking(id, s[2], database)
		} else if s[1] == "20" && s[2] == "Cooling" {
			println("Finish cooling")
			updateCooling(id, s[2], database)
		}
	}
}

func insertNewCooking(sondeID int, newCooking string, database *sql.DB) {
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

func updateCooking(sondeID int, finishCooking string, database *sql.DB) {
	var exist int
	row := database.QueryRow("SELECT IIF(EXISTS (SELECT * FROM SondesInfos WHERE sondeId = ? AND finishCooking = null), 1, 0)", strconv.Itoa(sondeID))
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

func updateCooling(sondeID int, finishCooling string, database *sql.DB) {
	var exist int
	row := database.QueryRow("SELECT IIF(EXISTS (SELECT * FROM SondesInfos WHERE sondeId = ? AND finishCooling = null), 1, 0)", strconv.Itoa(sondeID))
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
