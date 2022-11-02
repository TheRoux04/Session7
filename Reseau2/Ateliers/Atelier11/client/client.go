package main

import (
	"encoding/binary"
	"fmt"
	"net"
	"strconv"
)

func main() {
	dialer, err := net.Dial("tcp", ":8000")
	if err != nil {
		fmt.Println("Connexion couldn't be establish")
		return
	} else {
		fmt.Println("Connected to server")
	}

	defer func() {
		dialer.Close()
		fmt.Println("Connexion closed")
	}()

	for {
		var t uint8
		var l uint32
		binary.Read(dialer, binary.BigEndian, &t)
		binary.Read(dialer, binary.BigEndian, &l)
		var v = make([]byte, l)
		dialer.Read(v)
		switch t {
		case 1:
			fmt.Println(string(v))
			break
		case 2:
			fmt.Println(strconv.Atoi(string(v)))
			break
		}
	}
}
