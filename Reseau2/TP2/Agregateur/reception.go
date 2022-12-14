package main

import (
	"database/sql"
	"encoding/json"
	"fmt"
	"io"
	"log"
	"net/http"
	"net/url"
	"sync"
	"time"
)

type Reception struct {
	Timestamp  string `json:"timestamp"`
	CommandeId int    `json:"commandeId"`
	TotalPig   int    `json:"totalPig"`
	Pig        int    `json:"pig"`
	Piggy      int    `json:"piggy"`
	Pigget     int    `json:"pigget"`
}

func getReception(wg *sync.WaitGroup, database *sql.DB) {
	ticker := time.NewTicker(2 * time.Minute)
	fmt.Println("debut ecoute reception")
	var websiteUrl = "http://localhost:8080/api/reception"
	defer wg.Done()
	U, err := url.Parse(websiteUrl)
	if err != nil {
		panic(err)
	}
	func(U *url.URL) {
		for {
			request, _ := http.NewRequest(
				http.MethodGet,
				U.String(),
				nil,
			)
			request.Header.Add("Accept", "application/json")
			response, err := http.DefaultClient.Do(request)
			if err != nil {
				fmt.Println(err)
			} else {
				responseByte, err := io.ReadAll(response.Body)
				if err != nil {
					fmt.Println(err)
				} else {
					var reception []Reception
					json.Unmarshal(responseByte, &reception)
					insertReception(reception, database)
				}
			}
			<-ticker.C
		}
	}(U)
}

func insertReception(reception []Reception, db *sql.DB) {
	for _, reception := range reception {
		var count int
		row := db.QueryRow("SELECT COUNT(*) FROM reception WHERE time = ?", reception.Timestamp)
		row.Scan(&count)
		if count == 0 {
			statement, err := db.Prepare("INSERT INTO reception(timestamp, commandeId, totalPig, pig, piggy, pigget ) values(?,?,?,?,?,?) ")
			if err != nil {
				log.Fatal(err)
			}
			_, err = statement.Exec(reception.Timestamp, reception.CommandeId, reception.TotalPig, reception.Pig, reception.Piggy, reception.Pigget)
			if err != nil {
				log.Fatal(err)
			}
		}

	}
}
