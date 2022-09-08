package main

import "fmt"

func main() {
	var x, compte = 3, 1

	for x != 1 {
		compte++
		if x%2 == 0 {
			x /= 2
		} else {
			x = x*3 + 1
		}
	}

	fmt.Printf("Nombre: %d, Items dans la suite: %d", x, compte)
}
