package main

import (
	"net"
	"time"
)

func main() {
	listener, _ := net.ListenUDP("udp", &net.UDPAddr{Port: 8000})
	defer listener.Close()
	buf := make([]byte, 1024)
	for {
		_, clientAddr, _ := listener.ReadFromUDP(buf)
		go manageClient(listener, clientAddr)
	}
}

func manageClient(server *net.UDPConn, address *net.UDPAddr) {
	for {
		now := []byte(time.Now().Format(time.ANSIC))
		server.WriteToUDP(now, address)
		time.Sleep(time.Second)
	}
}
