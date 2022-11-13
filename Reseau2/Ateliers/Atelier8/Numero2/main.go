package main

import (
	"fmt"
	"sync"
	"time"
)

func main() {
	var m sync.Mutex
	var wg sync.WaitGroup
	for i := 1; i <= 10; i++ {
		wg.Add(1)
		go func(i int, m *sync.Mutex, wg *sync.WaitGroup) {
			defer wg.Done()
			s := "Goroutine"
			for _, r := range s {
				m.Lock()
				fmt.Printf("%c", r)
				m.Unlock()
				time.Sleep(100 * time.Millisecond)
			}
			fmt.Printf("#%d", i)
			fmt.Println()
		}(i, &m, &wg)
		wg.Wait()
	}
}

//var tick *time.Ticker = time.NewTicker(time.Second / 5)
//defer tick.Stop()
