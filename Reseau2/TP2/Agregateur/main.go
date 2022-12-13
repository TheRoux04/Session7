package main

func main() {
	database := initDatabase()

	go sondes(database.Database)
	go balance(database.Database)
}
