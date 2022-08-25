package main

import "fmt"

func main() {
	inc := func(no int) int {	//Mettre une fonction dans une variable
		return no + 1
	}
	x := 5
	x = inc(x)
	fmt.Println(x)
}

//Factoriel

func fact(x uint) uint {
	if x == 0 {
		return 1
	}
	return x * fact(x-1)
}

//********************************
//Tail Recursive
func main() {
	a := fact2(9)
	fmt.Println(a)
}

func factTR(n uint, a uint) uint {
	if n == 0 {
		return a
	}
	return factTR(n-1, n*a)
}

func fact2(x uint) uint {
	return factTR(x, 1)
}

//************************************