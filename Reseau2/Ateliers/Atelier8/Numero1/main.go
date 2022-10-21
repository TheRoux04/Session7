package main

import (
	"fmt"
	"sync"
	"sync/atomic"
)

func main() {
	var compte uint32 = 0
	var wg sync.WaitGroup
	for i := 1; i <= 1000; i++ {
		wg.Add(1)
		go func(compte *uint32, i int, wg *sync.WaitGroup) {
			defer wg.Done()
			if i%3 == 0 || i%5 == 0 {
				atomic.AddUint32(compte, 1)
			}
		}(&compte, i, &wg)
	}
	wg.Wait()
	fmt.Println(compte)
}
