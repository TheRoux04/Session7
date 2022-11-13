package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"net"
	"strings"
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
	for {

		msg, err := bufio.NewReader(c).ReadString('\n')
		if err != nil || (strings.Compare(msg, "close\n") == 0) {
			fmt.Printf("Deconnexion of client: %s\n", c.RemoteAddr().String())
			c.Close()
			return
		}

		_, err = io.WriteString(c, msg+"\n")
		if err != nil {
			fmt.Printf("Deconnexion of client: %s\n", c.RemoteAddr().String())
			c.Close()
			return
		}

		if msg != "close\n" {
			time.Sleep(time.Second)
			fmt.Printf("Message receive from client, %s : %s\n", c.RemoteAddr().String(), msg)
		}

		fmt.Print("Entrer quelque chose: ")
		fmt.Scanln(&msg)
	}
}

// Et mettre le listener en listenTCP
/*for {
	conn, err := listner.AcceptTCP()
	conn.SetKeepAlive(true)
	conn.SetKeepAlivePeriod(time.Second)
	if err != nil {
		log.Println(err)
		continue
	}
}*/
