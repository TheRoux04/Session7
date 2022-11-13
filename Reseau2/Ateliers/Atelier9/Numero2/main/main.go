package main

import (
	"fmt"
	"io"
	"log"
	"math/rand"
	"net"
	"strconv"
	"time"
)

func main() {
	listner, err := net.Listen("tcp", ":8000")
	if err != nil {
		log.Fatalln(err)
	}
	noClient := 1
	for {
		conn, err := listner.Accept()
		fmt.Println("New connexion client: ", noClient)
		if err != nil {
			log.Println(err)
			continue
		}
		go gererConnection(conn, noClient)
		noClient++
	}
}

func gererConnection(c net.Conn, noClient int) {
	defer c.Close()
	var nb int
	rand.Seed(time.Now().UnixNano())
	for {
		nb = rand.Intn(999) + 1
		_, err := io.WriteString(c, strconv.Itoa(nb)+"\n")
		if err != nil {
			return
		}
		fmt.Printf("Sent %d, to clent %d\n", nb, noClient)
		time.Sleep(time.Second)
	}
}
