package main

import (
	"database/sql"
	"fmt"
	"github.com/pion/dtls/v2"
	"log"
	"net"
	"strconv"
	"strings"
	"sync"
)

func sondes(wg *sync.WaitGroup, database *sql.DB) {
	defer wg.Done()
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
		/*fmt.Println(s[0])
		fmt.Println(s[1])
		fmt.Println(s[2])*/
		//fmt.Println(s[3])
		temperature, _ := strconv.Atoi(s[1])

		if temperature >= 20 && s[2] == "" {
			println("Start cooking")
			insertNewCooking(id, s[3], database)
		} else if temperature >= 200 && s[2] == "Cooking" {
			println("Finish cooking")
			println(s[1])
			updateCooking(id, s[3], database)
		} else if temperature == 20 && s[2] == "Cooling" {
			println("Finish cooling")
			println(s[1])
			updateCooling(id, s[3], database)
		}
	}
}

func insertNewCooking(sondeID int, newCooking string, database *sql.DB) {
	fmt.Println("Insert")
	println(strconv.Itoa(sondeID))
	println()
	statement, err := database.Prepare("INSERT INTO SondesInfos (sondeId, newCooking) VALUES (?, ?)")
	if err != nil {
		log.Fatal(err)
	}
	_, err = statement.Exec(strconv.Itoa(sondeID), newCooking)

	if err != nil {
		fmt.Println(err)
		return
	}
}

func updateCooking(sondeID int, finishCooking string, database *sql.DB) {
	println("Update cooked")
	println(strconv.Itoa(sondeID))
	println()
	statement, err := database.Prepare("UPDATE SondesInfos SET finishCooking = ? WHERE sondeId = ? AND finishCooking = ''")
	if err != nil {
		log.Fatal(err)
	}
	_, err = statement.Exec(finishCooking, strconv.Itoa(sondeID))
	if err != nil {
		return
	}
}

func updateCooling(sondeID int, finishCooling string, database *sql.DB) {
	println("Update cooled")
	println(strconv.Itoa(sondeID))
	println()
	statement, err := database.Prepare("UPDATE SondesInfos SET finishCooling = ? WHERE sondeId = ? AND finishCooling = ''")
	if err != nil {
		log.Fatal(err)
	}
	_, err = statement.Exec(finishCooling, strconv.Itoa(sondeID))
	if err != nil {
		return
	}
}
