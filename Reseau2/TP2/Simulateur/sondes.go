package main

import (
	"log"
	"math/rand"
	"net"
	"strconv"
	"time"
)

func udpNewConnection(listenerUDP net.Listener, connectionUDPChan chan<- net.Conn) {
	for {
		conn, err := listenerUDP.Accept()
		if err != nil {
			log.Fatalln(err)
		}
		connectionUDPChan <- conn
	}
}

func manageUDPConnection(sondeChan <-chan string, connectionUDPChan <-chan net.Conn) {
	connection := make(map[net.Conn]string)
	for {
		select {
		case newConn := <-connectionUDPChan:
			connection[newConn] = ""
		case newTemp := <-sondeChan:
			if len(connection) > 0 {
				for conn := range connection {
					conn.Write([]byte(newTemp))
					//println("Send")
				}
			}
		}
	}
}

func sondes(sondeChan chan<- string, id int) {
	rand.Seed(time.Now().UnixNano())
	var randTick int
	var temperature = 10
	var goodTemperature = false
	var changeTemperature = 0
	var state = ""

	var t int64
	ticker := time.NewTicker(1 * time.Second)

	for {
		if state == "Cooling" && temperature == 20 {
			temperature = 10
			goodTemperature = false
			changeTemperature = 0
			state = ""
		}

		if temperature == 10 && changeTemperature == 0 {
			randTick = 1
			//randTick = rand.Intn(12-1) + 1
			for i := 0; i < randTick; i++ {
				<-ticker.C
			}
			/*tm.MoveCursor(1, 1)
			tm.Clear()
			tm.Println(string(buf))
			tm.Flush()
			time.Sleep(time.Second / 10)*/
			changeTemperature = 1
		} else {
			changeTemperature = rand.Intn(20-10) + 10

			if state == "" && temperature >= 20 {
				state = "Cooking"
			}

			if !goodTemperature {
				temperature = temperature + changeTemperature
				if temperature >= 200 {
					goodTemperature = true
				}
			} else {
				if temperature-changeTemperature <= 20 {
					temperature = 20
				} else {
					temperature = temperature - changeTemperature
					state = "Cooling"
				}
			}

			<-ticker.C
			println("Sonde " + strconv.Itoa(id) + " : " + strconv.Itoa(temperature))
		}
		t = time.Now().Unix()

		println(state)
		sondeChan <- strconv.Itoa(id) + "/" + strconv.Itoa(temperature) + "/" + state + "/" + strconv.Itoa(int(t))

	}
}
