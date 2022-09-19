package main

//Go routine
/*
import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	for i := 0; i < 10; i++ {
		go compteur(i)
	}
	var input string
	fmt.Scanln(&input)
}

func compteur(n int) {
	for i := 0; i < 10; i++ {
		fmt.Println(n, ":", i)
		amt := time.Duration(rand.Intn(250))
		time.Sleep(time.Millisecond * amt)
	}
}*/

/*
import (
	"fmt"
	"time"
)

func main() {
	var oni chan string = make(chan string)
	go pinger(oni)
	go printer(oni)
	time.Sleep(time.Millisecond * 500)
	go ponger(oni)
	var input string
	fmt.Scanln(&input)
}

func pinger(c chan<- string) { //Juste en mode ecriture  	chan<-
	for {
		c <- "ping"
		time.Sleep(time.Second * 1)
	}
}

func ponger(c chan<- string) { //Juste en mode ecriture 	chan<-
	for {
		c <- "pong"
		time.Sleep(time.Second * 1)
	}
}

func printer(c <-chan string) { //Juste en mode lecture 	<-chan
	for {
		msg := <-c
		fmt.Println(msg)
	}
}*/

/*
func main() {
	nombres := make(chan int)
	carres := make(chan int)

	go Compteur(nombres)

	//Fonction anonyme
	go func(out chan<- int, in <-chan int) {
		for x := range in {
			out <- x * x
		}
	}(carres, nombres)

	go Carre(carres, nombres)
	for x := range carres {
		fmt.Println(x)
	}
}

func Compteur(out chan<- int) {
	for x := 0; x < 100; x++ {
		out <- x
	}
	defer close(out)
}

func Carre(out chan<- int, in <-chan int) {
	for x := range in {
		out <- x * x
	}
	defer close(out)
}
*/

/*
import (
	"fmt"
	"time"
)

func main() {
	maxGoroutines := 10
	guard := make(chan struct{}, maxGoroutines)

	for i := 0; i < 30; i++ {
		guard <- struct{}{} // bloque lorsqu'on arrive à maxGoroutines
		go func(n int) {
			worker(n)
			<-guard
		}(i)
	}
}

func worker(i int) {
	fmt.Println("travaille sur la tâche ", i)
	time.Sleep(5 * time.Second)
}*/

import (
	"fmt"
	"os"
	"time"
)

func main() {
	fmt.Println("Compte à rebours")
	abort := make(chan struct{})
	go func() {
		os.Stdin.Read(make([]byte, 1)) // read a single byte
		abort <- struct{}{}
	}()

	tick := time.NewTicker(1 * time.Second)

	for countdown := 10; countdown > 0; countdown-- {
		fmt.Printf("%v...", countdown)
		select {

		case <-tick.C: // Ne fait rien
		case <-abort:
			fmt.Println("Décollage annulé!")
			return // quitte la fonction main
		}
	}
	launch()
}

func launch() {
	fmt.Println("Décollage")
}
