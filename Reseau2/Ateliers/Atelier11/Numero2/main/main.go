package main

import (
	"encoding/binary"
	"fmt"
	"log"
	"net"
	"os"
	"os/signal"
	"time"
)

func main() {
	server, err := net.ListenTCP("tcp", &net.TCPAddr{Port: 8000})
	if err != nil {
		fmt.Println("Error : Count not listen on port 8000")
		log.Fatalln(err)
	} else {
		fmt.Println("Server is listening on port 8000")
	}

	go func(l *net.TCPListener) {
		sigchan := make(chan os.Signal)
		signal.Notify(sigchan, os.Interrupt)
		<-sigchan
		l.Close()
		os.Exit(0)
	}(server)

	for {
		conn, err2 := server.AcceptTCP()
		conn.SetKeepAlive(true)
		conn.SetKeepAlivePeriod(time.Second * 5)
		if err2 != nil {
			log.Println(err2)
			fmt.Printf("Deconnexion of client: %s\n", conn.RemoteAddr().String())
			continue
		}
		fmt.Println("Connexion receive from:", conn.RemoteAddr())
		go gererConnection(conn)

		if conn.RemoteAddr() == nil {
			time.Sleep(time.Second)
			fmt.Printf("Deconnexion of client: %s\n", conn.RemoteAddr().String())
		}

		if err != nil {
			fmt.Println("Server closed")
			log.Fatalln(err)
		}
	}

}

func gererConnection(c *net.TCPConn) {
	defer func() {
		c.Close()
		fmt.Println("Connexion closed")
	}()
	var msg string
	for {
		fmt.Print("Entrer qqch: ")
		fmt.Scanln(&msg)

		var t = uint8(1)

		binary.Write(c, binary.BigEndian, t)
		var l = uint32(len(msg))
		binary.Write(c, binary.BigEndian, l)
		c.Write([]byte(msg))

	}
}
