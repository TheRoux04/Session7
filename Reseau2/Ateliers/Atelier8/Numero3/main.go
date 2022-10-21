package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

func main() {
	var m sync.RWMutex
	var n int = rand.Intn(100)
	var wg sync.WaitGroup
	for w := 0; w < 10; w++ {
		wg.Add(1)
		go func(nb *int, m *sync.RWMutex, w int, wg *sync.WaitGroup) {
			defer wg.Done()
			time.Sleep(time.Duration(rand.Intn(10)) * time.Millisecond)
			fmt.Printf("Lecteur %d se réveille\n", w)
			m.RLock()
			fmt.Printf("Lecture %d regarde\n", w)
			time.Sleep(2 * time.Second)
			fmt.Printf("Lecture %d affiche: %d\n", w, *nb)
			m.RUnlock()
		}(&n, &m, w, &wg)
	}

	for i := 0; i < 2; i++ {
		wg.Add(1)
		go func(nb *int, m *sync.RWMutex, i int, wg *sync.WaitGroup) {
			defer wg.Done()
			m.Lock()
			fmt.Printf("Ecrivain %d à modifier\n", i)
			m.Unlock()
		}(&n, &m, i, &wg)
	}

	wg.Wait()
}
