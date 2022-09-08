package main

import (
	"flag"
	"fmt"
)

// Passer des parametres en ligne de commande
func main() {
	deverminagePtr := flag.Bool("v", false, "afficher plus de détail")
	var deverminagePtr2 *bool
	flag.BoolVar(deverminagePtr2, "v2", false, "")
	flag.Parse()

	if *deverminagePtr {
		fmt.Println("Plus de détail")
	}
	fmt.Println("Bonjour monde")
}
