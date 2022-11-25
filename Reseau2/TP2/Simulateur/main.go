package main

import (
	"fmt"
	"math/rand"
	"net"
	"strconv"
	"time"
)

func main() {
	listener, _ := net.ListenUDP("udp", &net.UDPAddr{Port: 8000})
	defer listener.Close()
	buf := make([]byte, 1024)

	for {
		var sondeChan = make(chan string)
		for i := 0; i < 10; i++ {
			go sondes(i, sondeChan)
		}
		go noConnnect(sondeChan)
		for {
			_, clientAddr, _ := listener.ReadFromUDP(buf)
			go manage(sondeChan, listener, clientAddr)
		}
	}

}

func noConnnect(sondeChan <-chan string) {
	for {
		<-sondeChan
		//time.Sleep(time.Second * 5)
		println("No connect")
	}
}

func manage(sondeChan <-chan string, server *net.UDPConn, address *net.UDPAddr) {
	for {
		//server.WriteToUDP([]byte(<-sondeChan), address)
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
			sondeChan <- strconv.Itoa(temperature)
		}

		changeTemperature = rand.Intn(20-10) + 10
		if temperature >= 200 {
			time.Sleep(time.Second * 5)
			goodTemperature = true
			sondeChan <- strconv.Itoa(temperature)
		}

		if !goodTemperature {
			temperature = temperature + changeTemperature
		} else {
			if temperature-changeTemperature <= 20 {
				temperature = 20
				sondeChan <- strconv.Itoa(temperature)
			} else {
				temperature = temperature - changeTemperature
				sondeChan <- strconv.Itoa(temperature)
			}
		}

		if temperature == 20 {
			temperature = 10
		}

		println("Sonde " + strconv.Itoa(id) + " : " + strconv.Itoa(temperature))
		time.Sleep(time.Second * 5)
	}

}
