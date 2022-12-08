package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"math/rand"
	"net"
	"strconv"
	"time"
)

func main() {
	rand.Seed(time.Now().UnixNano())
	var randNumber int
	dialer, err := net.Dial("tcp", ":8000")
	defer dialer.Close()
	if err != nil {
		log.Fatalln(err)
	}
	for {
		randNumber = rand.Intn(1000-0) + 0
		//write to server
		_, err := io.WriteString(dialer, strconv.Itoa(randNumber)+"\n")
		if err != nil {
			fmt.Println("Connexion lost with server")
			dialer.Close()
			return
		}
		fmt.Print("Number: ", randNumber)

		msg, err := bufio.NewReader(dialer).ReadString('\n')
		if err != nil {
			log.Fatalln(err)
		}
		//strip the newline
		msg = msg[:len(msg)-1]
		fmt.Println(" -> Index: ", msg)
		time.Sleep(time.Second)
	}
}
