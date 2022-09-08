package main

import (
	"fmt"
	"math/rand"
	"time"
)

var cache map[int]int = make(map[int]int)

func main() {
	rand.Seed(time.Now().UnixNano())
	for i := 0; i < 100; i++ {
		var x int = rand.Intn(199) + 1
		fmt.Printf("%d - %d\n", x, syracuse(x))
	}
	fmt.Println("%v\n", cache)
}

func syracuse(x int) int {
	if compte, ok := cache[x]; ok {
		return compte
	}

	if x%2 == 0 {
		x /= 2
	} else {
		x = x*3 + 1
	}

	if x == 1 {
		return 1
	} else {
		var compte int = syracuse(x) + 1
		cache[x] = compte
		return compte
	}
}
