package main

import (
	"fmt"
	"log"
	"net"
	"os"
	"os/signal"
	"time"
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

	buf := make([]byte, 1024)
	for {
		_, clientAddr, err := server.ReadFromUDP(buf)
		if err != nil {
			continue
		}

		if string(buf) == "exit" {
			fmt.Println("Client disconnected")
			continue
		}

		go manageClient(server, clientAddr)
	}
}

func manageClient(server *net.UDPConn, address *net.UDPAddr) {
	for {
		now := []byte(time.Now().Format(time.ANSIC))
		server.WriteToUDP(now, address)
		time.Sleep(time.Second)
	}
}
