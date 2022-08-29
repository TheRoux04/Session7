package main

import "fmt"

func main() {
	//Le make est une autre facon d'instancier
	var s = make([]int, 10, 20)


	//Map cest un dictionnaire dansas présent les indice sont des string et les valeurs sont des int
	var x map[string]int = make(map[string]int)
	x["clé"] = 10
	delete(x, "clé")
	fmt.Println(x)
	
}
