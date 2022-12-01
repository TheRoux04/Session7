package main

import (
	"fmt"
	"github.com/pion/dtls/v2"
	"net"
)

func main() {
	config := &dtls.Config{
		InsecureSkipVerify: true,
	}
	conn, _ := dtls.Dial("udp", &net.UDPAddr{Port: 8000}, config)
	for {
		var buffer = make([]byte, 256)
		conn.Read(buffer)
		fmt.Println(string(buffer))
	}
}
