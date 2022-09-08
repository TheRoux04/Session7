package main

import "fmt"

func main() {
	var x1, x2, compte, end = 0, 1, 1, 7
	tab := []int{0, 1}

	for compte < end {
		compte++
		x3 := x1 + x2
		x1 = x2
		x2 = x3
		tab = append(tab, x3)
	}

	fmt.Printf("%d nombre de fibonaccci: %v", end, tab)
}
