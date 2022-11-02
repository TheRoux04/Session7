package main

import (
	"encoding/binary"
	"fmt"
	"log"
	"net"
	"time"
)

func main() {
	listner, err := net.Listen("tcp", ":8000")
	if err != nil {
		fmt.Println("Error : Count not listen on port 8000")
		log.Fatalln(err)
	} else {
		fmt.Println("Server is listening on port 8000")
	}

	for {
		conn, err2 := listner.Accept()
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

func gererConnection(c net.Conn) {
	defer c.Close()
	var msg string
	for {
		fmt.Print("Entrer qqch: ")
		fmt.Scanln(&msg)

		var t = uint8(1)

		binary.Write(c, binary.BigEndian, t)
		var l = uint32(len(msg))
		binary.Write(c, binary.BigEndian, l)
		c.Write([]byte(msg))

		//Pour string
		//var l = uint32(len(v))
		//c.Write([]byte(v))

		//Pour Int
		/*
			var l = uint32(len(string(v)))
			c.Write([]byte(string(v)))
		*/

	}
}
