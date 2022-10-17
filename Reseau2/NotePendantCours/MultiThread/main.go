package main

import (
	"fmt"
	"sync"
)

// Ce n'est plus réelement multiThread avec "atomic ou Mutex" puisqu'il s'exécute un apres l'autre
func main() {
	var compte uint32 = 0
	var wg sync.WaitGroup
	var m sync.Mutex
	for i := 0; i < 10000; i++ {
		wg.Add(1)
		go func(compte *uint32, wg *sync.WaitGroup, m *sync.Mutex) {
			defer wg.Done()
			//atomic.AddUint32(compte, 1) Seulement applicable pour les int, plus rapide pour les entiers
			m.Lock()
			*compte++
			m.Unlock()
		}(&compte, &wg, &m)
	}
	wg.Wait()
	fmt.Println(compte)
}
