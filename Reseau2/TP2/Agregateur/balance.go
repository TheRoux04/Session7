package main

import (
	"crypto/tls"
	"database/sql"
	"encoding/binary"
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
	} else {
		var t uint8
		var l uint32
		for {
			binary.Read(dialer, binary.BigEndian, &t)
			if t == 1 {
				binary.Read(dialer, binary.BigEndian, &l)
				var v = make([]byte, l)
				dialer.Read(v)
				fmt.Print(string(v))
				tm, pigType, weight, decimals := decode(string(v))
				insertBalance(tm, pigType, weight, decimals, database)

			}
		}
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
