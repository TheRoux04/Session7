package main

import (
	"net"
	"os"
	"os/signal"
	"time"
)

func main() {
	udpServer, err := net.ResolveUDPAddr("udp", ":8000")
	if err != nil {
		panic(err)
	}
	conn, err := net.DialUDP("udp", nil, udpServer)
	if err != nil {
		panic(err)
	}

	go func(l *net.UDPAddr, c *net.UDPConn) {
		sigchan := make(chan os.Signal)
		signal.Notify(sigchan, os.Interrupt)
		<-sigchan
		conn.Close()
		conn.Write([]byte("exit"))
		os.Exit(0)
	}(udpServer, conn)

	defer conn.Close()
	conn.Write([]byte("Connect pls"))
	for {
		buf := make([]byte, 1024)
		conn.Read(buf)
		println(string(buf))
		time.Sleep(time.Second)
	}
}
