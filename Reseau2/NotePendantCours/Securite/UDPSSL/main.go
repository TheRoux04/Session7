package main

import (
	"crypto/tls"
	"fmt"
	"github.com/pion/dtls/v2"
	"net"
	"strconv"
	"time"
)

func main() {
	go server()
	client()
}

func server() {
	cert, _ := tls.LoadX509KeyPair("localhost/cert.pem", "localhost/key.pem")
	config := &dtls.Config{
		Certificates: []tls.Certificate{cert},
	}
	listener, _ := dtls.Listen("udp", &net.UDPAddr{Port: 8000}, config)
	for {
		conn, _ := listener.Accept()
		go func(conn net.Conn) {
			i := 0
			for {
				stream := []byte(strconv.Itoa(i))
				conn.Write(stream)
				time.Sleep(time.Second)
				i++
			}
		}(conn)
	}
}

func client() {
	config := &dtls.Config{
		InsecureSkipVerify: true,
	}
	conn, _ := dtls.Dial("udp", &net.UDPAddr{Port: 8000}, config)
	for {
		var buffer = make([]byte, 256)
		conn.Read(buffer)
		fmt.Println(string(buffer))
	}
}
