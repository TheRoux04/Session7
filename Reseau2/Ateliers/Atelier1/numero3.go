package main

import "fmt"

func main() {
	x := []int{48, 96, 86, 68, 57, 82, 63, 70, 37, 34, 83, 27, 19, 97, 9, 17}

	min, max, moy := minmaxmoy(x)

	fmt.Printf("Tableau: %v\n", x)
	fmt.Printf("Min: %d, Max: %d, Moyenne: %d", min, max, moy)
}

func minmaxmoy(tab []int) (int, int, int) {
	var min, max, moy, sum int = tab[0], tab[0], 0, 0

	for _, num := range tab {
		sum += num
		if num < min {
			min = num
		}
		if num > max {
			max = num
		}
	}

	moy = sum / len(tab)

	return min, max, moy
}
