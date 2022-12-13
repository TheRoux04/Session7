package main

import (
	"fmt"
	"io"
	"log"
	"math/rand"
	"net"
	"strconv"
	"time"
)

func tcpNewConnection(listenerTCP net.Listener, connectionTCPChan chan<- net.Conn, balanceChan chan<- string) {
	var connect = false
	for {
		conn, err := listenerTCP.Accept()
		if err != nil {
			log.Fatalln(err)
		}
		connectionTCPChan <- conn

		if !connect {
			go balance(balanceChan)
			connect = true
		}
	}
}

func manageTCPConnection(balanceChan <-chan string, connectionTCPChan <-chan net.Conn) {
	connection := make(map[net.Conn]string)
	for {
		select {
		case newConn := <-connectionTCPChan:
			connection[newConn] = ""
		case newWeight := <-balanceChan:
			if len(connection) > 0 {
				for conn := range connection {
					_, err := io.WriteString(conn, newWeight)
					if err != nil {
						return
					}
					println("Send")
				}
			}
		}
	}
}

func balance(balanceChan chan<- string) {
	rand.Seed(time.Now().UnixNano())

	for {
		randTime := rand.Intn(30-5) + 5

		ticker := time.NewTicker(time.Duration(randTime) * time.Second)
		<-ticker.C

		timestamp := fmt.Sprintf("%X", time.Now().Unix())
		//data to binary
		pigType := fmt.Sprintf("%02b", int64(rand.Intn(3-1)+1))
		weight := fmt.Sprintf("%09b", int64(rand.Intn(511-1)+1))
		decimals := fmt.Sprintf("%05b", int64(rand.Intn(9-1)+1)/10)

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
