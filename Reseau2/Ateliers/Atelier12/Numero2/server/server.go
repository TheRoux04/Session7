package main

import (
	"net"
)

func main() {
	server, _ := net.ListenUDP("udp", &net.UDPAddr{Port: 8000})
	defer server.Close()
	buf := make([]byte, 1024)
	for {
		_, clientAddr, _ := server.ReadFromUDP(buf)
		go manageClient(server, clientAddr)
	}
}

func manageClient(server *net.UDPConn, address *net.UDPAddr) {
	for {
		server.WriteToUDP([]byte("(ᴗ˳ᴗ)"), address)
		server.WriteToUDP([]byte("(ᴗ˳ᴗ) z"), address)
		server.WriteToUDP([]byte("(ᴗ˳ᴗ) zZ"), address)
		server.WriteToUDP([]byte("(ᴗ˳ᴗ) zZᶻ"), address)
		server.WriteToUDP([]byte("(ᴗ˳ᴗ) zZ"), address)
		server.WriteToUDP([]byte("(ᴗ˳ᴗ) z"), address)
		server.WriteToUDP([]byte("(ᴗ˳ᴗ)"), address)
	}
}
