package main

import "fmt"

// https://gosamples.dev/unix-time/ for timestamp

func main() {
	//go sondeMain()
	go balanceMain()
	//go receptionMain()

	//waitgroup
	var input string
	fmt.Scanln(&input)
}
