package main

import (
	"crypto/tls"
	"flag"
	"fmt"
	"strconv"
	"time"
)

func main() {
	config := tls.Config{InsecureSkipVerify: true}
	dialer, err := tls.Dial("tcp", "localhost:8082", &config)
	if err != nil {
		fmt.Println(err)
	}
	var msgToSend string
	showBalances := flag.Bool("b", false, "Afficher les balances")
	showSondes := flag.Bool("s", false, "Afficher les sondes")
	showReceptions := flag.Bool("r", false, "Afficher les réceptions")
	duration := flag.Int("d", 0, "Durée en minutes à afficher")

	// Parsing des flags
	flag.Parse()

	// Afficher les balances si le flag -b est présent
	if *showBalances {
		msgToSend = "b"
	}

	// Afficher les sondes si le flag -s est présent
	if *showSondes {
		msgToSend = "s"
	}

	// Afficher les réceptions si le flag -r est présent
	if *showReceptions {
		msgToSend = "r"
	}

	// Si aucun flag n'a été spécifié, on affiche un message d'erreur et on quitte
	if !*showBalances && !*showSondes && !*showReceptions {
		fmt.Println("Aucune section à afficher. Veuillez spécifier au moins un flag : -b, -s ou -r")
		return
	}

	// Si la durée n'a pas été spécifiée, afficher un message d'erreur
	if *duration == 0 {
		fmt.Println("Aucune durée spécifiée. Veuillez spécifier une durée en minutes avec le flag -d")
		return
	}

	// Calcul de la date limite à partir de la durée spécifiée en flag
	if *duration > 0 {
		t := time.Now().Unix()
		msgToSend = msgToSend + "/" + strconv.Itoa(*duration) + "/" + strconv.Itoa(int(t))
	}

	// Envoi du message au serveur
	println(msgToSend)
	_, err = dialer.Write([]byte(msgToSend))

	for {
		// Lecture de la réponse du serveur
		buf := make([]byte, 1024)
		n, err := dialer.Read(buf)
		if err != nil {
			fmt.Println(err)
			return
		}
		fmt.Println(string(buf[:n]))
	}

}
