package main

import (
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"net/url"
)

type DogFact struct {
	Facts   []string `json:"facts"`
	Success bool     `json:"success"`
}

func main() {
	var webSiteURL = "https://dog-api.kinduff.com/api/facts"
	u, _ := url.Parse(webSiteURL)

	values, _ := url.ParseQuery(u.RawQuery)
	values.Set("number", "1")
	u.RawQuery = values.Encode()

	req, _ := http.NewRequest(http.MethodGet, u.String(), nil)

	req.Header.Add("Accept", "application/json")

	res, _ := http.DefaultClient.Do(req)
	responseBytes, _ := io.ReadAll(res.Body)

	var dogFact DogFact
	json.Unmarshal(responseBytes, &dogFact)

	fmt.Print(dogFact)

}
