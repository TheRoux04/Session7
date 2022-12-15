package main

import (
	"bufio"
	"container/list"
	"crypto/tls"
	"database/sql"
	"fmt"
	"log"
	"net"
	"strconv"
	"strings"
	"sync"
	"time"
)

func monitor(wg *sync.WaitGroup, database *sql.DB) {
	defer wg.Done()
	cert, err := tls.LoadX509KeyPair("../localhost/cert.pem", "../localhost/key.pem")
	if err != nil {
		log.Fatal(err)
	}
	tlsCfg := &tls.Config{Certificates: []tls.Certificate{cert}}
	listenerTCP, err := tls.Listen("tcp", "localhost:8082", tlsCfg)
	if err != nil {
		fmt.Println(err)
	}

	for {
		conn, err := listenerTCP.Accept()
		if err != nil {
			log.Fatalln(err)
		}
		go handleConnection(conn, database)
	}
}

func handleConnection(conn net.Conn, database *sql.DB) {
	defer func() {
		conn.Close()
		fmt.Println("Connexion closed")
	}()
	listElement := list.New()
	for {
		//read the message
		msg, err := bufio.NewReader(conn).ReadBytes('\n')
		if err != nil {
			fmt.Println(err)
		}
		//strip the \n
		msg = msg[:len(msg)-1]
		//split the message with /
		s := strings.Split(string(msg), "/")
		timeMinute, _ := strconv.Atoi(s[1])
		println(s)
		if s[0] == "b" {
			listElement = getBalances(timeMinute, s[2], database)
		} else if s[0] == "s" {
			listElement = getSondes(timeMinute, s[2], database)
		} else if s[0] == "r" {
			listElement = getReceptions(timeMinute, s[2], database)
		}

		//send each element of the list to the server
		for e := listElement.Front(); e != nil; e = e.Next() {
			conn.Write([]byte(e.Value.(string) + "\n"))
		}

	}
}

func getSondes(timeMinute int, tNow string, database *sql.DB) *list.List {
	listSondes := list.New()
	statement, err := database.Prepare("SELECT * FROM SondesInfos ORDER BY id ASC")
	if err != nil {
		log.Fatal(err)
	}
	rows, err := statement.Query()
	if err != nil {
		log.Fatal(err)
	}
	for rows.Next() {
		var id int
		var idSonde int
		var start sql.NullString
		var finishCooking sql.NullString
		var finishCooling sql.NullString

		err = rows.Scan(&id, &idSonde, &start, &finishCooking, &finishCooling)
		if err != nil {
			log.Fatal(err)
		}
		if start.Valid {
			startCook, err := time.Parse("2006-01-02 15:04:05", start.String)
			if err != nil {
				log.Fatal(err)
			}
			timeNow, err := time.Parse("2006-01-02 15:04:05", tNow)
			if err != nil {
				log.Fatal(err)
			}
			if timeNow.Sub(startCook).Minutes() < float64(timeMinute) {
				listSondes.PushBack(string(rune(idSonde)) + "/" + start.String + "/" + finishCooking.String + "/" + finishCooling.String)
			}
		}

	}
	return listSondes
}

func getBalances(timeMinute int, tNow string, database *sql.DB) *list.List {
	//List of string with format "timestamp/pigType/weight/decimals"
	listBalances := list.New()
	statement, err := database.Prepare("SELECT * FROM BalancesInfos ORDER BY id ASC")
	if err != nil {
		log.Fatal(err)
	}
	rows, err := statement.Query()
	if err != nil {
		log.Fatal(err)
	}
	for rows.Next() {
		var id int
		var timeArrived sql.NullString
		var pigType int
		var weight int
		var decimals int
		err = rows.Scan(&id, &timeArrived, &pigType, &weight, &decimals)
		if err != nil {
			log.Fatal(err)
		}
		if timeArrived.Valid {
			timestamp, err := time.Parse("2006-01-02 15:04:05", timeArrived.String)
			if err != nil {
				log.Fatal(err)
			}
			timeNow, err := time.Parse("2006-01-02 15:04:05", tNow)
			if err != nil {
				log.Fatal(err)
			}
			if timeNow.Sub(timestamp).Minutes() < float64(timeMinute) {
				listBalances.PushBack(timeArrived.String + "/" + string(rune(pigType)) + "/" + string(rune(weight)) + "/" + string(rune(decimals)))
			}
		}
	}
	return listBalances
}

func getReceptions(timeMinute int, tNow string, database *sql.DB) *list.List {
	//List of string with format "timestamp/commandeId/totalPig/pig/piggy/pigget"
	listReceptions := list.New()
	statement, err := database.Prepare("SELECT * FROM ReceptionInfos ORDER BY id ASC")
	if err != nil {
		log.Fatal(err)
	}
	rows, err := statement.Query()
	if err != nil {
		log.Fatal(err)
	}
	for rows.Next() {
		var id int
		var timeArrived sql.NullString
		var commandeId int
		var totalPig int
		var pig int
		var piggy int
		var pigget int
		err = rows.Scan(&id, &timeArrived, &commandeId, &totalPig, &pig, &piggy, &pigget)
		if err != nil {
			log.Fatal(err)
		}
		if timeArrived.Valid {
			timestamp, err := time.Parse("2006-01-02 15:04:05", timeArrived.String)
			if err != nil {
				log.Fatal(err)
			}
			timeNow, err := time.Parse("2006-01-02 15:04:05", tNow)
			if err != nil {
				log.Fatal(err)
			}
			if timeNow.Sub(timestamp).Minutes() < float64(timeMinute) {
				listReceptions.PushBack(timeArrived.String + "/" + string(rune(commandeId)) + "/" + string(rune(totalPig)) + "/" + string(rune(pig)) + "/" + string(rune(piggy)) + "/" + string(rune(pigget)))
			}
		}
	}
	return listReceptions
}
