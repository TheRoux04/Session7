package main

import (
	tm "github.com/buger/goterm"
	"net"
	"time"
)

func main() {
	udpServer, _ := net.ResolveUDPAddr("udp", ":8000")
	conn, _ := net.DialUDP("udp", nil, udpServer)
	defer conn.Close()
	conn.Write([]byte("Connect pls"))
	for {
		buf := make([]byte, 1024)
		conn.Read(buf)

		tm.MoveCursor(1, 1)
		tm.Clear()
		tm.Println(string(buf))
		tm.Flush()
		time.Sleep(time.Second / 10)
	}
}
