package main

import "sync"

func main() {
	var database Db
	database = initDatabase()

	var wg sync.WaitGroup
	//wg.Add(1)
	//go getReception(&wg, database.Database)
	wg.Add(1)
	go sondes(&wg, database.Database)
	wg.Add(1)
	go balance(&wg, database.Database)
	//wg.Add(1)
	//go monitor(&wg, database.Database)
	wg.Wait()
}
