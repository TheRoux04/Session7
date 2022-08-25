package main

import "fmt"

func main() {
	v := [9]int{133, 22, 31, 234, 45, 3, 23, 34, 12}

	for i := 0; i < len(v)-1; i++ {
		for j := i + 1; j < len(v); j++ {
			if v[i] > v[j] {
				v[i], v[j] = v[j], v[i]
			}
		}
	}

	fmt.Printf("%v", v)
}
