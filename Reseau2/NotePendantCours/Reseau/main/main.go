package main

import (
	"io"
	"log"
	"net"
	"time"
)

func main() {
	listner, err := net.Listen("tcp", ":8000")
	if err != nil {
		log.Fatalln(err)
	}
	for {
		conn, err := listner.Accept()
		if err != nil {
			log.Println(err)
			continue
		}
		go gererConnection(conn)
	}
}

func gererConnection(c net.Conn) {
	defer c.Close()
	for {
		_, err := io.WriteString(c, time.Now().Format("15:04:05\n"))
		if err != nil {
			return
		}
		time.Sleep(time.Second)
	}
}