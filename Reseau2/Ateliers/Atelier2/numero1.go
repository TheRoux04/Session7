package main

import (
	"fmt"
	"strings"
)

func main() {
	var s string = "La patate douce n’est pas apparentée à la pomme de terre, malgré son nom. Elle est dotée d'une très grande richesse en pro-vitamine A (ou bêta-carotène). Elle fournit aussi une énergie de longue durée, grâce à l’amidon qu’elle renferme."
	fmt.Printf(strings.ToLower(s))
	s = strings.Replace(s, "'", " ", -1)
	s = strings.Replace(s, "(", "", -1)
	s = strings.Replace(s, ")", "", -1)
	s = strings.Replace(s, ".", "", -1)
	s = strings.Replace(s, ",", "", -1)
	var x = make(map[string]int)
	words := strings.Split(s, " ")

	for i := 0; i < len(s)-1; i++ {
		if s[] {
			
		}
	}
}
