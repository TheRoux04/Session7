package main

import (
	"bufio"
	"crypto/tls"
	"database/sql"
	"fmt"
	"log"
	"strconv"
	"sync"
	"time"
)

type Balance struct {
	Time     string
	Type     int64
	Weight   int64
	Decimals int64
}

func balance(wg *sync.WaitGroup, database *sql.DB) {
	defer wg.Done()
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
		newBalance := decode(string(msg))
		insertBalance(newBalance, database)
	}
}

func decode(data string) Balance {
	tm, err := strconv.ParseInt(data[0:8], 16, 64)
	if err != nil {
		panic(err)
	}
	timestamp := time.Unix(tm, 0).Format("02 January 2006 15h04")

	last4, err := strconv.ParseUint(data[8:12], 16, 64)
	if err != nil {
		fmt.Println(err)
	}

	sixteenBits := fmt.Sprintf("%016b", last4)

	pigType, err := strconv.ParseUint(sixteenBits[0:2], 2, 64)
	if err != nil {
		fmt.Println(err)
	}

	weight, err := strconv.ParseUint(sixteenBits[2:11], 2, 64)
	if err != nil {
		fmt.Println(err)
	}

	decimals, err := strconv.ParseUint(sixteenBits[11:16], 2, 64)
	if err != nil {
		fmt.Println(err)
	}

	return Balance{timestamp, int64(pigType), int64(weight), int64(decimals)}
}

func insertBalance(newBalance Balance, database *sql.DB) {
	statement, err := database.Prepare("INSERT INTO BalancesInfos (timestamp, pigType, weight, decimals) VALUES (?, ?, ?, ?)")
	if err != nil {
		log.Fatal(err)
	}
	_, err = statement.Exec(newBalance.Time, newBalance.Type, newBalance.Weight, newBalance.Decimals)
	if err != nil {
		return
	}
}
