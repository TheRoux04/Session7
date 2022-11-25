package main

import (
	"net"
)

func main() {
	udpServer, _ := net.ResolveUDPAddr("udp", ":8000")
	conn, _ := net.DialUDP("udp", nil, udpServer)
	defer conn.Close()
	conn.Write([]byte("Connect pls"))
	for {
		buf := make([]byte, 1024)
		conn.Read(buf)
		println(buf)
	}
}
