package main

import (
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"net/url"
)

type Sonde struct {
	sondeId       int
	NewCooking    string
	FinishCooking string
	FinishCooling string
}

func apiSondes(URL string) {
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
				var allSondes []Sonde
				json.Unmarshal(responseByte, &allSondes)
				displaySondes(allSondes)
			}
		}
	}(urlWeb)
}

func displaySondes(allSondes []Sonde) {
	for _, sonde := range allSondes {
		fmt.Println("Sondes id: ", sonde.sondeId, ", Start cooking: ", sonde.NewCooking, ", Finish cooking: ", sonde.FinishCooking, ", Finish cooling: ", sonde.FinishCooling)
	}
}
