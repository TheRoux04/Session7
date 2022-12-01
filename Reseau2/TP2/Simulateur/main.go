package main

import (
	"crypto/tls"
	"fmt"
	"github.com/pion/dtls/v2"
	"math/rand"
	"net"
	"strconv"
	"time"
)

func main() {
	cert, _ := tls.LoadX509KeyPair("localhost/cert.pem", "localhost/key.pem")
	config := &dtls.Config{
		Certificates: []tls.Certificate{cert},
	}
	listener, _ := dtls.Listen("udp", &net.UDPAddr{Port: 8000}, config)
	for {
		var sondeChan = make(chan string)
		var connectionChan = make(chan net.Conn)
		for i := 0; i < 10; i++ {
			go sondes(i, sondeChan)
		}
		go manageConnection(sondeChan)
		for {
			conn, _ := listener.Accept()
			connectionChan <- conn
		}
	}
}

func manageConnection(sondeChan <-chan string, connectionChan <-chan net.Conn) {
	connection := make(map[net.Conn]string)
	for {
		select {
		case newConn := <-connectionChan:
			connection[newConn] = ""
		case newTemp := <-sondeChan:
			for conn, _ := range connection {
				stream := []byte(data)
				_, err := conn.Write(stream)
				if err != nil {
					return
				}
			}

		}
		fmt.Println(<-sondeChan)
		//time.Sleep(time.Second * 5)
		println("Send")
	}
}

func sondes(id int, sondeChan chan<- string) {
	rand.Seed(time.Now().UnixNano())
	var randTick int
	var temperature = 10
	var goodTemperature = false
	var changeTemperature int
	randTick = rand.Intn(11) + 1

	for {
		if temperature == 10 {
			for i := 0; i < randTick; i++ {
				time.Sleep(time.Second * 5)
			}
			t := time.Now().Unix()
			sondeChan <- "Sonde " + strconv.Itoa(id) + "/ Start /" + strconv.FormatInt(t, 10)
		}

		changeTemperature = rand.Intn(20-10) + 10
		if temperature >= 200 {
			time.Sleep(time.Second * 5)
			goodTemperature = true
			t := time.Now().Unix()
			sondeChan <- "Sonde " + strconv.Itoa(id) + "/ Cooked /" + strconv.FormatInt(t, 10)
		}

		if !goodTemperature {
			temperature = temperature + changeTemperature
		} else {
			t := time.Now().Unix()
			if temperature-changeTemperature <= 20 {
				temperature = 20
				sondeChan <- "Sonde " + strconv.Itoa(id) + "/ Ready /" + strconv.FormatInt(t, 10)
			} else {
				temperature = temperature - changeTemperature
				sondeChan <- "Sonde " + strconv.Itoa(id) + "/ Ready /" + strconv.FormatInt(t, 10)
			}
		}

		if temperature == 20 {
			temperature = 10
		}

		println("Sonde " + strconv.Itoa(id) + " : " + strconv.Itoa(temperature))
		time.Sleep(time.Second * 5)
	}

}
