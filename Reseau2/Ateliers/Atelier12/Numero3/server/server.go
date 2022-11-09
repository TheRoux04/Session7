package main

import (
	"fmt"
	"log"
	"net"
	"os"
	"os/signal"
)

func main() {
	server, err := net.ListenUDP("udp", &net.UDPAddr{Port: 8000})
	if err != nil {
		fmt.Println("Error : Count not listen on port 8000")
		log.Fatalln(err)
	} else {
		fmt.Println("Server is listening on port 8000")
	}

	go func(l *net.UDPConn) {
		sigchan := make(chan os.Signal)
		signal.Notify(sigchan, os.Interrupt)
		<-sigchan
		l.Close()
		os.Exit(0)
	}(server)
	timeToWait := 5
	waiting := 0
	defer server.Close()
	buf := make([]byte, 1024)
	for {
		_, clientAddr, err := server.ReadFromUDP(buf)
		if err != nil {
			continue
		}
		for i, _ := range server.RemoteAddr().Network() {
			if int8(i) == clientAddr.String()[int8(i)] {

			}
		}
		waiting++
		if timeToWait*3 == waiting {
			waiting = 0
			go manageClient(server, clientAddr)
		}

		if string(buf) == "exit" {
			fmt.Println("Client disconnected")
			continue
		} else if string(buf) == "heartBeat" {

		}
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
