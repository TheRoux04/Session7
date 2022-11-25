package main

import (
	"bufio"
	"crypto/tls"
	"fmt"
	"time"
)

func main() {
	config := tls.Config{InsecureSkipVerify: true}
	dialer, _ := tls.Dial("tcp", "localhost:8001", &config)
	for {
		message, _ := bufio.NewReader(dialer).ReadString('\n')
		fmt.Print("->", message)
		time.Sleep(time.Second)
	}
}
