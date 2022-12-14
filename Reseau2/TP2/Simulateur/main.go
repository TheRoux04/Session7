package main

import (
	"crypto/tls"
	"fmt"
	"github.com/pion/dtls/v2"
	"net"
)

// https://gosamples.dev/unix-time/ for timestamp

func main() {
	listenerUDP, err := dtls.Listen("udp", &net.UDPAddr{Port: 8000}, getDtlsCertificat().cfgDtls)
	if err != nil {
		fmt.Println(err)
	}

	listenerTCP, err := tls.Listen("tcp", "localhost:8081", getCertificat().cfgTls)
	if err != nil {
		fmt.Println(err)
	}

	var sondeChan = make(chan string)
	var balanceChan = make(chan string)
	var connectionUDPChan = make(chan net.Conn)
	var connectionTCPChan = make(chan net.Conn)

	for i := 0; i < 4; i++ {
		//go sondes(sondeChan, i)
	}
	go udpNewConnection(listenerUDP, connectionUDPChan)
	go tcpNewConnection(listenerTCP, connectionTCPChan, balanceChan)
	go manageUDPConnection(sondeChan, connectionUDPChan)
	go manageTCPConnection(balanceChan, connectionTCPChan)

	//waitgroup
	var input string
	println("Press any key to exit")
	fmt.Scanln(&input)

}
