package main

import (
	"container/list"
	"database/sql"
	"fmt"
	_ "github.com/mattn/go-sqlite3"
	"log"
	"os"
	"time"
)

type Db struct {
	Database *sql.DB
}

func initDatabase() Db {
	if _, err := os.Stat("./Database/TP2Boucherie.db"); err == nil {
		fmt.Printf("Database exists\n")
	} else {
		file, err := os.Create("./Database/TP2Boucherie.db")
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
    	"sondeId" INTEGER NOT NULL,
    	"newCooking" TEXT DEFAULT '',
    	"finishCooking" TEXT DEFAULT '',
    	"finishCooling" TEXT DEFAULT ''
        );`
	query, err := database.Prepare(sondesInfos)
	if err != nil {
		log.Fatal(err)
	}
	query.Exec()

	balancesInfos := `CREATE TABLE IF NOT EXISTS BalancesInfos (
    	"id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    	"timestamp" TEXT,
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
        "timestamp" TEXT,
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

func (database *Db) getSondes(subMin int, tNow string) *list.List {
	listSondes := list.New()

	stmt, err := database.Database.Prepare("SELECT * FROM SondesInfos ORDER BY id ASC")
	if err != nil {
		log.Fatal(err)
	}
	rows, err := stmt.Query()
	if err != nil {
		log.Fatal(err)
	}
	for rows.Next() {
		var id int
		var start sql.NullString
		var finishCooking sql.NullString
		var finishCooling sql.NullString
		var idSonde int
		err = rows.Scan(&id, &start, &finishCooking, &finishCooling, &idSonde)
		if err != nil {
			log.Fatal(err)
		}
		if start.Valid {
			startCook, err := time.Parse("2006-01-02 15:04:05", start.String)
			if err != nil {
				log.Fatal(err)
			}
			timeNow, err := time.Parse("2006-01-02 15:04:05", tNow)
			if err != nil {
				log.Fatal(err)
			}
			if timeNow.Sub(startCook).Minutes() < float64(subMin) {
				listSondes.PushBack(string(idSonde) + "/" + start.String + "/" + finishCooking.String + "/" + finishCooling.String)
			}
		}
	}
	return listSondes
}

func (database *Db) getReceptions(subMin int, tmtNow string) *list.List {
	listRecept := list.New()
	stmt, err := database.Database.Prepare("SELECT * FROM ReceptionsInfos ORDER BY timestamp ASC")
	if err != nil {
		log.Fatal(err)
	}
	rows, err := stmt.Query()
	if err != nil {
		log.Fatal(err)
	}
	for rows.Next() {
		var arriver sql.NullString
		var numero int
		var total int
		var porcs int
		var porcelets int
		var truies int
		err = rows.Scan(&arriver, &numero, &total, &porcs, &porcelets, &truies)
		if err != nil {
			log.Fatal(err)
		}
		if arriver.Valid {
			timeArriver, err := time.Parse("2006-01-02 15:04:05", arriver.String)
			if err != nil {
				log.Fatal(err)
			}
			timeNow, err := time.Parse("2006-01-02 15:04:05", tmtNow)
			if err != nil {
				log.Fatal(err)
			}
			if timeNow.Sub(timeArriver).Minutes() < float64(subMin) {
				listRecept.PushBack(Reception{arriver.String, numero, total, porcs, porcelets, truies})
			}
		}
	}
	return listRecept
}

func (database *Db) getBalances(subMin int, tmtNow string) *list.List {
	listBalance := list.New()
	stmt, err := database.Database.Prepare("SELECT * FROM BalancesInfos ORDER BY timestamp ASC")
	if err != nil {
		log.Fatal(err)
	}
	rows, err := stmt.Query()
	if err != nil {
		log.Fatal(err)
	}
	for rows.Next() {
		var timestamp sql.NullString
		var typePig int
		var weight int
		var decimals int
		err = rows.Scan(&timestamp, &typePig, &weight, &decimals)
		if err != nil {
			log.Fatal(err)
		}
		if timestamp.Valid {
			timeTemps, err := time.Parse("02 January 2006 15h04", timestamp.String)
			if err != nil {
				log.Fatal(err)
			}
			timeNow, err := time.Parse("02 January 2006 15h04", tmtNow)
			if err != nil {
				log.Fatal(err)
			}
			fmt.Println(timeNow.Sub(timeTemps).Minutes())
			if timeNow.Sub(timeTemps).Minutes() < float64(subMin) {
				listBalance.PushBack(timestamp.String + "/" + string(typePig) + "/" + string(weight) + "/" + string(decimals))
			}
		}
	}
	return listBalance
}
