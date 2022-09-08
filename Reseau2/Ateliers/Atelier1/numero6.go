package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
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
			fmt.Printf("Est premier: %d", nb)
		} else {
			fmt.Printf("N'est pas premier: %d\n", nb)
		}
	}
}
