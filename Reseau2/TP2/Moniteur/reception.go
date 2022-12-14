package main

import (
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"net/url"
)

type Reception struct {
	Time   string
	comId  int
	Total  int
	Pig    int
	Piggy  int
	Pigget int
}

func apiReceptions(URL string) {
	urlWeb, err := url.Parse(URL)
	if err != nil {
		panic(err)
	}
	func(urlWeb *url.URL) {
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
				var allReceptions []Reception
				json.Unmarshal(responseByte, &allReceptions)
				displayReceptions(allReceptions)
			}
		}
	}(urlWeb)
}

func displayReceptions(allReceptions []Reception) {
	for _, reception := range allReceptions {
		fmt.Println("Commande id: ", reception.comId, ", Time arrival: ", reception.Time, ", Total: ", reception.Total, ", Pig: ", reception.Pig, ", Piggy: ", reception.Piggy, ", Pigget: ", reception.Pigget)
	}
}
