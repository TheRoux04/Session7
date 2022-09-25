package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	var c chan int = make(chan int)
	go printer(c)
	for i := 0; i < 10; i++ {
		go estPremierB(c)

	}
	var input string
	fmt.Scanln(&input)
}

func estPremierB(c chan int) {
	rand.Seed(time.Now().UnixNano())
	var isPrime bool = false
	var nb int

	for !isPrime {
		nb = rand.Intn(999) + 1
		i := nb - 1
		for i > 1 {
			if nb%i == 0 {
				break
			}
			i--
		}
		if i == 1 {
			isPrime = true
			c <- nb
		}
	}
}

func printer(c chan int) {
	for {
		msg := <-c
		fmt.Println(msg)
		time.Sleep(time.Second * 1)
	}
}
