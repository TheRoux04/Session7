package main

import (
	"crypto/tls"
	"fmt"
	"io"
	"log"
	"math/rand"
	"net"
	"strconv"
	"time"
)

type Balance struct {
	Time     int64
	Type     int64
	Weight   int64
	Decimals int64
}

func balanceMain() {

	listenerTCP, err := tls.Listen("tcp", "localhost:8081", getCertificat().cfgTls)
	if err != nil {
		fmt.Println(err)
	}

	var balanceChan = make(chan string)
	var connectionTCPChan = make(chan net.Conn)

	go tcpNewConnection(listenerTCP, connectionTCPChan, balanceChan)
	go manageTCPConnection(balanceChan, connectionTCPChan)

}

func tcpNewConnection(listenerTCP net.Listener, connectionTCPChan chan<- net.Conn, balanceChan chan<- string) {
	var connect = false
	for {
		conn, err := listenerTCP.Accept()
		if err != nil {
			log.Fatalln(err)
		}
		if !connect {
			go balance(balanceChan)
			connect = true
		}
		connectionTCPChan <- conn
	}
}

func manageTCPConnection(balanceChan <-chan string, connectionTCPChan <-chan net.Conn) {
	connectionTCP := make(map[net.Conn]string)
	for {
		select {
		case newConn := <-connectionTCPChan:
			connectionTCP[newConn] = ""
		case newWeight := <-balanceChan:
			if len(connectionTCP) > 0 {
				for conn := range connectionTCP {
					_, err := io.WriteString(conn, newWeight+"\n")
					if err != nil {
						return
					}
					println("Send")
				}
			}

		}
	}
}

func newBalance() Balance {
	return Balance{
		Time:     time.Now().Unix(),
		Type:     int64(rand.Intn(4 - 0)),
		Weight:   int64(rand.Intn(511-1) + 1),
		Decimals: int64(rand.Intn(9-1) + 1),
	}
}

func balance(balanceChan chan<- string) {
	rand.Seed(time.Now().UnixNano())

	for {
		newBalance := newBalance()
		randTime := rand.Intn(30-5) + 5

		ticker := time.NewTicker(time.Duration(randTime) * time.Second)
		<-ticker.C

		timestamp := fmt.Sprintf("%X", newBalance.Time)
		//data to binary
		pigType := fmt.Sprintf("%02b", newBalance.Type)
		weight := fmt.Sprintf("%09b", newBalance.Weight)
		decimals := fmt.Sprintf("%05b", newBalance.Decimals)

		allHexa := pigType + weight + decimals

		//convert to uint
		i, err := strconv.ParseUint(allHexa, 2, 16)
		if err != nil {
			fmt.Println(err)
		}
		//uint to hex
		allHexa = fmt.Sprintf("%X", i)

		println(timestamp + allHexa)
		balanceChan <- timestamp + allHexa

	}
}
