package main

import "fmt"

func main() {
	v := [9]int{133, 22, 31, 234, 45, 3, 23, 34, 12}
	v1 := v[:len(v)-1]

	for i := range v1 {
		v2 := v[i+1:]
		for j := range v2 {
			if v[i] > v[j] {
				v[i], v[j] = v[j], v[i]
			}
		}
	}

	fmt.Printf("%v", v)
}
