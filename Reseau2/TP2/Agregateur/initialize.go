package main

import (
	"database/sql"
	"fmt"
	"log"
	"os"
)

type Db struct {
	Database *sql.DB
}

func initDatabase() Db {
	if _, err := os.Stat("TP2Boucherie.db"); err == nil {
		fmt.Printf("Database exists\n")
	} else {
		file, err := os.Create("TP2Boucherie.db")
		if err != nil {
			log.Fatal(err)
		}
		file.Close()
	}
	database := openConnection()
	createTable(database)
	return Db{database}
}

func openConnection() *sql.DB {
	database, err := sql.Open("sqlite3", "./Database/TP2Boucherie.db")
	if err != nil {
		log.Fatal(err)
	}
	return database
}

func createTable(database *sql.DB) {

	sondesInfos := `CREATE TABLE IF NOT EXISTS SondesInfos (
    	"id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    	"newCooking" TEXT,
    	"finishCooking" TEXT,
    	"finishCooling" TEXT
        );`
	query, err := database.Prepare(sondesInfos)
	if err != nil {
		log.Fatal(err)
	}
	query.Exec()

	balancesInfos := `CREATE TABLE IF NOT EXISTS BalancesInfos (
    	"id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    	"timestamp" TEXT PRIMARY KEY,
    	"pigType" INT,
    	"weight" INT,
    	"decimals" INT
    	);`
	query, err = database.Prepare(balancesInfos)
	if err != nil {
		log.Fatal(err)
	}
	query.Exec()

	receptionsInfos := `CREATE TABLE IF NOT EXISTS ReceptionsInfos (
    	"id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
        "time" TEXT,
        "commandeId" INT,
        "totalPig" INT,
        "pig" INT,
        "piggy" INT,
        "pigget" INT
        );`
	query, err = database.Prepare(receptionsInfos)
	if err != nil {
		log.Fatal(err)
	}
	query.Exec()
}
