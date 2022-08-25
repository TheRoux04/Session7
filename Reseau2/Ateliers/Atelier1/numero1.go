package main

import "fmt"

func main() {
	fmt.Print("Entrer un nombre réel: ")
	var i float32
	fmt.Scanf("%f", &i)
	fmt.Printf("%f", i * 2)
}


