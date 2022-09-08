package main

import (
	"fmt"
	"log"
	"regexp"
	"strings"
)

func main() {
	var s string = "La patate douce n’est pas apparentée à la pomme de terre, malgré son nom. Elle est dotée d'une très grande richesse en pro-vitamine A (ou bêta-carotène). Elle fournit aussi une énergie de longue durée, grâce à l’amidon qu’elle renferme."
	var dist = make(map[string]int)

	s = strings.ReplaceAll(s, "'", " ")

	re, err := regexp.Compile(`[\.,\(\)]`)
	if err != nil {
		log.Fatalln(err)
	}
	s = re.ReplaceAllString(s, "")

	var words []string = strings.Fields(s)

	for _, word := range words {
		if count, ok := dist[word]; ok {
			dist[word] = count + 1
		} else {
			dist[word] = 1
		}
	}

	fmt.Printf("Le tableau: %v", dist)
}
