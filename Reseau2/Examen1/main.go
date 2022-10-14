package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	var oni chan string = make(chan string)
	go ping(oni)
	go printer(oni)
	time.Sleep(time.Millisecond * 500)
	go pong(oni)
	var input string
	fmt.Scanln(&input)

	rand.Seed(time.Now().UnixNano())

}

func ping(c chan<- string) { //Juste en mode ecriture  	chan<-
	var nb int
	for {
		nb = rand.Intn(100)
		if nb < 91 {
			c <- "ping"
		} else {
			c <- "pongWin"
		}
		time.Sleep(time.Second * 1)
	}
}

func pong(c chan<- string) { //Juste en mode ecriture 	chan<-
	var nb int
	for {

		nb = rand.Intn(100)
		if nb < 91 {
			c <- "pong"
		} else {
			c <- "pingWin"
		}

		time.Sleep(time.Second * 1)
	}
}

func printer(c <-chan string) { //Juste en mode lecture 	<-chan
	scorePing := 0
	scorePong := 0
	for {
		msg := <-c
		if msg == "pingWin" {
			scorePing++
			fmt.Printf("Point pour ping:, score %d - %d", scorePing, scorePong)
			fmt.Println()
		} else if msg == "pongWin" {
			scorePong++
			fmt.Printf("Point pour pong:, score %d - %d", scorePing, scorePong)
			fmt.Println()
		} else {
			fmt.Println(msg)
		}

	}
}

/*
func main() {

	chan1 := make(chan int, 5)
	chan2 := make(chan int, 5)
	chan3 := make(chan int, 5)
	chan4 := make(chan int, 5)
	chan5 := make(chan int, 5)
	chan6 := make(chan int, 5)

	rand.Seed(time.Now().UnixNano())
	go fct1(chan1, chan2)
	go printer(chan6, nb)
	go fct2(chan2, chan3)
	go fct3(chan3, chan4)
	go fct4(chan4, chan5)
	go fct5(chan5, chan6)
	go fct6(chan6)

	var nb int
	for i := 0; i < 100; i++ {
		nb = rand.Intn(100)
		fmt.Printf("Nombre aléatoire: %d", nb)
		fmt.Println()
		chan1 <- nb
	}

	var input string
	fmt.Scanln(&input)
}

func fct1(nbReceve <-chan int, nbSent chan<- int) {
	for {
		fmt.Println("fct1")
		nb := <-nbReceve
		nbSent <- nb * 2
	}
}

func fct2(nbReceve <-chan int, nbSent chan<- int) {
	for {
		println("fct2")
		nb := <-nbReceve
		nbSent <- nb / 3
	}
}

func fct3(nbReceve <-chan int, nbSent chan<- int) {
	for {
		println("fct3")
		nb := <-nbReceve
		nbSent <- nb - 10
	}
}

func fct4(nbReceve <-chan int, nbSent chan<- int) {
	for {
		println("fct4")
		nb := <-nbReceve
		if nb < 0 {
			nb = 0
		}
		nbSent <- nb
	}
}

func fct5(nbReceve <-chan int, nbSent chan<- int) {
	for {
		println("fct5")
		nb := <-nbReceve
		nbSent <- nb + 1
	}
}

func fct6(nbReceve <-chan int) {
	for {
		println("fct6")
		msg := <-nbReceve
		fmt.Println(msg)
	}
}

func printer(nbReceve <-chan int, nb int) {
	for {
		msg := <-nbReceve
		fmt.Printf("Nombre aleatoire: %d", nb)
		fmt.Println()
		fmt.Printf("Résultat: %d", msg)
		fmt.Println()
	}
}

*/

/*
func main() {
	nb := 0
	i := 1
	continu := true
	var input int
	fmt.Scanln(&input)
	fmt.Print("n=", nb)
	for continu {
		nb = i * i
		if nb < input {
			i++
		} else {
			i--
			continu = false
		}
	}

	total := 0
	totalString := ""
	for t := 1; t <= i; t++ {
		total += t
		if t == 1 {
			totalString += ", " + strconv.Itoa(t)
		} else {
			totalString += " + " + strconv.Itoa(t)
		}
	}
	fmt.Println(totalString + " = " + strconv.Itoa(total))
}
*/