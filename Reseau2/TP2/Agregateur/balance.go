package main

import (
	"bufio"
	"crypto/tls"
	"database/sql"
	"fmt"
	"log"
	"strconv"
	"time"
)

func balance(database *sql.DB) {
	fmt.Println("Balance started")
	config := tls.Config{InsecureSkipVerify: true}
	dialer, err := tls.Dial("tcp", "localhost:8081", &config)
	if err != nil {
		fmt.Println(err)
	}
	for {
		msg, err := bufio.NewReader(dialer).ReadBytes('\n')
		if err != nil {
			fmt.Println(err)
		}
		println("msg: ", string(msg))
		//strip the \n
		msg = msg[:len(msg)-1]
		tm, pigType, weight, decimals := decode(string(msg))
		insertBalance(tm, pigType, weight, decimals, database)
	}
}

func decode(data string) (string, int, int, int) {
	tm, err := strconv.ParseInt(data[0:8], 16, 64)
	if err != nil {
		panic(err)
	}
	timestamp := time.Unix(tm, 0).Format("02 January 2006 15h04")

	//convert the last 4 digits to uint
	last4, err := strconv.ParseUint(data[8:12], 16, 64)
	if err != nil {
		fmt.Println(err)
	}
	//convert to binary (16 bits)
	sixteenBits := fmt.Sprintf("%016b", last4)
	//convert to uint
	pigType, err := strconv.ParseUint(sixteenBits[0:2], 2, 64)
	if err != nil {
		fmt.Println(err)
	}
	//convert to uint
	weight, err := strconv.ParseUint(sixteenBits[2:11], 2, 64)
	if err != nil {
		fmt.Println(err)
	}
	//convert to uint
	decimals, err := strconv.ParseUint(sixteenBits[11:16], 2, 64)
	if err != nil {
		fmt.Println(err)
	}
	println("timestamp: ", timestamp)
	println("pigType: ", int(pigType))
	println("weight: ", int(weight))
	println("decimals: ", int(decimals))
	return timestamp, int(pigType), int(weight), int(decimals)
}

// insert Balance
func insertBalance(timestamp string, pigType int, weight int, decimals int, database *sql.DB) {
	statement, err := database.Prepare("INSERT INTO BalancesInfos (timestamp, pigType, weight, decimals) VALUES (?, ?, ?, ?)")
	if err != nil {
		log.Fatal(err)
	}
	_, err = statement.Exec(timestamp, pigType, weight, decimals)
	if err != nil {
		return
	}
}
