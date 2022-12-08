package main

import (
	"fmt"
	"github.com/pion/dtls/v2"
	"log"
	"net"
)

func main() {
	var compte = 0
	config := &dtls.Config{
		InsecureSkipVerify: true,
	}
	conn, err := dtls.Dial("udp", &net.UDPAddr{Port: 8000}, config)
	if err != nil {
		log.Fatal(err)
	}
	conn.Write([]byte("Connexion"))
	for {
		var buffer = make([]byte, 256)
		_, err := conn.Read(buffer)
		if err != nil {
			return
		}

		if buffer != nil {
			fmt.Print(string(buffer))
			compte++
		}
		println()
		if compte == 10 {
			compte = 0
			conn.Write([]byte("Much more"))
			println("Much more")
		}
	}
}
