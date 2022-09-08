package main

import "fmt"

func main() {
	var x int = 5
	add(&x, 4, 1, 2, 3)
	fmt.Println(x)
	add(&x)
	fmt.Println(x)
}

func add(x *int, nombres ...int) {
	var somme int = *x

	for _, n := range nombres {
		somme += n
	}

	*x = somme
}
