package main

import (
	"crypto/tls"
	"fmt"
	"github.com/pion/dtls/v2"
	"log"
	"net"
)

// https://gosamples.dev/unix-time/ for timestamp

var id = 0

func main() {
	cert, _ := tls.LoadX509KeyPair("localhost/cert.pem", "localhost/key.pem")
	config := &dtls.Config{
		Certificates: []tls.Certificate{cert},
	}
	listenerUDP, _ := dtls.Listen("udp", &net.UDPAddr{Port: 8000}, config)

	listenerTCP, err := net.Listen("tcp", ":8001")
	if err != nil {
		log.Fatalln(err)
	}

	var sondeChan = make(chan string)
	var balanceChan = make(chan string)
	var connectionUDPChan = make(chan net.Conn)
	var connectionTCPChan = make(chan net.Conn)

	for i := 0; i < 10; i++ {
		go sondes(sondeChan)
	}
	go udpNewConnection(listenerUDP, connectionUDPChan)
	go tcpNewConnection(listenerTCP, connectionTCPChan, balanceChan)
	go manageUDPConnection(sondeChan, connectionUDPChan)
	go manageTCPConnection(sondeChan, connectionUDPChan)

	//waitgroup
	var input string
	println("Press any key to exit")
	fmt.Scanln(&input)

}
