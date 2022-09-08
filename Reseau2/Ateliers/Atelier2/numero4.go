package main

import (
	"fmt"
	"log"
	"regexp"
)

func main() {
	var telephone string = "4504772305987"
	normaliser(&telephone)
	fmt.Println(telephone)
}

func normaliser(telephone *string) {
	var normal string
	var tel string

	re, err := regexp.Compile(`[^\d]`)
	if err != nil {
		log.Fatal(err)
	}

	tel = re.ReplaceAllString(*telephone, "")

	if len(tel) < 10 {
		log.Fatal("Le numéro doit avoir au minimum 10 chiffres")
	}

	normal = tel[:3]
	normal += "-"
	normal += tel[3:6]
	normal += "-"
	normal += tel[6:10]

	if len(*telephone) > 10 {
		normal += " poste "
		normal += (*telephone)[10:]
	}

	*telephone = normal
}
