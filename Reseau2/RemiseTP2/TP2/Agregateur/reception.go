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
	fmt.Println("Ecoute reception")
	var websiteUrl = "http://localhost:8089/api/reception"
	defer wg.Done()
	urlWeb, err := url.Parse(websiteUrl)
	if err != nil {
		panic(err)
	}
	func(urlWeb *url.URL) {
		for {
			request, _ := http.NewRequest(
				http.MethodGet,
				urlWeb.String(),
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

					for _, reception := range reception {
						var count int
						row := database.QueryRow("SELECT COUNT(*) FROM ReceptionsInfos WHERE time = ?", reception.Timestamp)
						row.Scan(&count)
						if count == 0 {
							statement, err := database.Prepare("INSERT INTO ReceptionsInfos(time, commandeId, totalPig, pig, piggy, pigget ) values(?,?,?,?,?,?) ")
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
			}
			<-ticker.C
		}
	}(urlWeb)
}
