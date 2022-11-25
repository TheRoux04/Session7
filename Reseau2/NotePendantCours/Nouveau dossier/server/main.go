package main

import (
	"crypto/tls"
	"io"
	"net"
	"time"
)

func main() {
	cert, _ := tls.LoadX509KeyPair("../localhost/cert.pem", "../localhost/key.pem")
	tlsCfg := &tls.Config{Certificates: []tls.Certificate{cert}}
	server, _ := tls.Listen("tcp", "localhost:8001", tlsCfg)
	for {
		conn, _ := server.Accept()
		go func(conn net.Conn) {
			for {
				io.WriteString(conn, "toto\n")
				time.Sleep(time.Second)
			}
		}(conn)
	}
}
