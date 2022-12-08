package main

import (
	"bufio"
	"os"
)

func main() {

	cles := lireCles()
	//afficher contenu de cles
	for _, cle := range cles {
		println(cle)
	}

	//ecrireFichier(cles)

}

func ecrireFichier(cles []string) {
	file, _ := os.OpenFile("cles.txt", os.O_TRUNC|os.O_CREATE|os.O_WRONLY, 0644)

	datawriter := bufio.NewWriter(file)

	for _, data := range cles {
		datawriter.WriteString(data + "\n")
	}

	datawriter.Flush()
	file.Close()
}

func lireCles() []string {
	f, _ := os.Open("cles.txt")
	scanner := bufio.NewScanner(f)
	result := []string{}
	for scanner.Scan() {
		line := scanner.Text()
		result = append(result, line)
	}
	return result
}
