package main

import (
	"crypto/tls"
	"github.com/pion/dtls/v2"
	"io"
	"log"
	"math/rand"
	"net"
	"strconv"
	"time"
)

// https://gosamples.dev/unix-time/ for timestamp

var id = 0

func main() {
	cert, _ := tls.LoadX509KeyPair("localhost/cert.pem", "localhost/key.pem")
	config := &dtls.Config{
		Certificates: []tls.Certificate{cert},
	}
	listener, _ := dtls.Listen("udp", &net.UDPAddr{Port: 8000}, config)

	listner, err := net.Listen("tcp", ":8001")
	if err != nil {
		log.Fatalln(err)
	}

	var sondeChan = make(chan string)
	var balanceChan = make(chan string)
	var connectionChan = make(chan net.Conn)
	var asConnection = false
	for i := 0; i < 10; i++ {
		//go sondes(sondeChan)
	}
	go manageConnection(sondeChan, balanceChan, connectionChan)
	for {
		conn, _ := listener.Accept()
		connectionChan <- conn
		if !asConnection {
			go balance(balanceChan)
			asConnection = true
		}
	}
}

func manageConnection(sondeChan <-chan string, balanceChan <-chan string, connectionChan <-chan net.Conn) {
	connection := make(map[net.Conn]string)
	for {
		select {
		case newConn := <-connectionChan:
			connection[newConn] = ""

		case newTemp := <-sondeChan:
			if len(connection) > 0 {
				for conn := range connection {
					conn.Write([]byte(newTemp))
					println("Send")
				}
			}
		case newWeight := <-balanceChan:
			if len(connection) > 0 {
				for conn := range connection {
					_, err := io.WriteString(conn, newWeight)
					if err != nil {
						return
					}
					println("Send")
				}
			}
		}
	}
}

func sondes(sondeChan chan<- string) {
	rand.Seed(time.Now().UnixNano())
	var randTick int
	var temperature = 10
	var goodTemperature = false
	var changeTemperature int
	randTick = rand.Intn(11) + 1
	var idSonde = 0
	ticker := time.NewTicker(5 * time.Second)

	for {
		if temperature == 10 {
			id++
			idSonde = id
			for i := 0; i < randTick; i++ {
				<-ticker.C
			}
			t := time.Now().Unix()
			sondeChan <- strconv.Itoa(idSonde) + "/Start/" + strconv.FormatInt(t, 10)
		}
		changeTemperature = rand.Intn(20-10) + 10
		<-ticker.C

		if temperature >= 200 {
			goodTemperature = true
			t := time.Now().Unix()
			sondeChan <- strconv.Itoa(idSonde) + "/Cooked/" + strconv.FormatInt(t, 10)
		}

		if !goodTemperature {
			temperature = temperature + changeTemperature
		} else {
			t := time.Now().Unix()
			if temperature-changeTemperature <= 20 {
				temperature = 20
				sondeChan <- strconv.Itoa(idSonde) + "/Ready/" + strconv.FormatInt(t, 10)
			} else {
				temperature = temperature - changeTemperature
			}
		}

		if temperature == 20 {
			temperature = 10
		}

		println("Sonde " + strconv.Itoa(idSonde) + " : " + strconv.Itoa(temperature))
	}
}

func balance(balanceChan chan<- string) {
	rand.Seed(time.Now().UnixNano())
	var randTime int
	var weight int  //max 511
	var decimal int //max 31
	var typePorc string
	var allString string

	decimal = rand.Intn(10)

	for {
		randTime = rand.Intn(30-5) + 5
		weight = rand.Intn(511-0) + 0
		decimal = rand.Intn(31-0) + 0
		ticker := time.NewTicker(time.Duration(randTime) * time.Second)
		<-ticker.C

		t := time.Now().Unix()
		//convert timestamp Unix to hexademical
		timestamp := strconv.FormatInt(t, 16)

		typePorc = "00"
		//convert string typePorc to binary
		binaryTypePorc := strconv.FormatInt(int64(typePorc[0]), 2)

		//convert int to binary
		weightBinaire := strconv.FormatInt(int64(weight), 2)
		decimalBinaire := strconv.FormatInt(int64(decimal), 2)

		//all string
		allString = timestamp + binaryTypePorc + weightBinaire + decimalBinaire

		//convert string to int
		allInt, _ := strconv.Atoi(allString)

		//convert int to hexademical
		allHexa := strconv.FormatInt(int64(allInt), 16)

		//convert hexademical to string
		allString = strconv.FormatInt(int64(allHexa[0]), 2)

		//balanceChan <- allString
		println(allString)

	}
}
