package main

import (
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"net/url"
)

type Balance struct {
	Time     string
	Type     int64
	Weight   int64
	Decimals int64
}

func apiBalances(URL string) {
	urlWeb, err := url.Parse(URL)
	if err != nil {
		panic(err)
	}
	func(webUrl *url.URL) {
		request, _ := http.NewRequest(
			http.MethodGet,
			webUrl.String(),
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
				var allBalances []Balance
				json.Unmarshal(responseByte, &allBalances)
				displayBalances(allBalances)
			}
		}
	}(urlWeb)
}

func displayBalances(allBalances []Balance) {
	for _, balance := range allBalances {
		fmt.Println("Time: ", balance.Time, ", Type: ", balance.Type, ", Weight: ", balance.Weight, ".", balance.Decimals, "kg")
	}
}
