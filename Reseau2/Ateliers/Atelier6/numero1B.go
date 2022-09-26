package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	rand.Seed(time.Now().UnixNano())
	var c chan int = make(chan int)
	for i := 0; i < 10; i++ {
		go estPremierB(c)

	}

	var countDone = 0
	for countDone < 10 {
		nb := <-c
		fmt.Printf("Est premier: %d\n", nb)
		countDone++
	}
	var input string
	fmt.Scanln(&input)
}

func estPremierB(c chan int) {
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
