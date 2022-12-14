package main

import "sync"

func main() {
	var database Db
	database = initDatabase()
	api := newApiAgreggateur(database.Database)
	var wg sync.WaitGroup
	//wg.Add(1)
	go getReception(&wg, database.Database)
	//wg.Add(1)
	//go sondes(database.Database)
	wg.Add(1)
	go balance(database.Database)
	//startApi(api)
	wg.Wait()

	//go sondes(database.Database)
	//go balance(database.Database)
}
