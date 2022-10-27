package main

import (
	"bufio"
	"fmt"
	"io"
	"net"
	"time"
)

func main() {
	dialer, err := net.Dial("tcp", ":8000")
	if err != nil {
		fmt.Println("Connexion couldn't be establish")
		return
	} else {
		fmt.Println("Connected to server")
	}

	var msg string
	defer func() {
		dialer.Close()
		fmt.Println("Connexion closed")
	}()

	for {
		fmt.Print("Entrer quelque chose: ")
		fmt.Scanln(&msg)

		_, err := io.WriteString(dialer, msg+"\n")
		if err != nil {
			fmt.Println("Connexion lost with server")
			dialer.Close()
			return
		}

		if msg == "close" {
			dialer.Close()
			return
		}

		message, err := bufio.NewReader(dialer).ReadString('\n')
		if err != nil {
			fmt.Println("Cant read message from server")
			dialer.Close()
		}

		if dialer != nil {
			time.Sleep(time.Second)
			fmt.Println("Message recu from server: ", message)
		}

	}
}
