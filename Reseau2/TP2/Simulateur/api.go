package main

import (
	"container/list"
	"encoding/json"
	"fmt"
	"github.com/gorilla/mux"
	"net/http"
	"strconv"
	"time"
)

type ApiAgreggateur struct {
	Reception *list.List
	Sonde     *list.List
	Balance   *list.List
	bd        *Db
}

func newApiAgreggateur(database *Db) *ApiAgreggateur {
	return &ApiAgreggateur{
		Reception: list.New(),
		Sonde:     list.New(),
		Balance:   list.New(),
		bd:        database,
	}
}

func startApi(api *ApiAgreggateur) {
	fmt.Println("Launch API")
	routeur := mux.NewRouter()
	routeur.HandleFunc("/api/sondes/{nb}", api.apiSondes).Methods("GET")
	routeur.HandleFunc("/api/balances/{nb}", api.apiBalances).Methods("GET")
	routeur.HandleFunc("/api/receptions/{nb}", api.apiReceptions).Methods("GET")
	http.ListenAndServe(":8089", routeur)
}

func (api *ApiAgreggateur) apiBalances(w http.ResponseWriter, r *http.Request) {
	var balanceJSON []BalanceJson
	params := mux.Vars(r)
	nb, _ := strconv.Atoi(params["nb"])
	tmt := time.Now().Format("02 January 2006 15h04")
	api.Balance = api.bd.getBalances(nb, tmt)
	for e := api.Balance.Front(); e != nil; e = e.Next() {
		balanceJSON = append(balanceJSON, e.Value.(Balance))
	}
	err := json.NewEncoder(w).Encode(balanceJSON)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}
}

func (api *ApiAgreggateur) apiReceptions(w http.ResponseWriter, r *http.Request) {
	var receptionsJSON []Reception
	params := mux.Vars(r)
	nb, _ := strconv.Atoi(params["nb"])
	tmt := time.Now().Format("2006-01-02 15:04:05")
	api.Reception = api.bd.getReceptions(nb, tmt)
	for e := api.Reception.Front(); e != nil; e = e.Next() {
		receptionsJSON = append(receptionsJSON, e.Value.(Reception))
	}
	err := json.NewEncoder(w).Encode(receptionsJSON)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}
}

func (api *ApiAgreggateur) apiSondes(w http.ResponseWriter, r *http.Request) {
	var sondesJSON []Sonde
	params := mux.Vars(r)
	nbMin, _ := strconv.Atoi(params["nb"])
	tmt := time.Now().Format("2006-01-02 15:04:05")
	//requete pour recuperer les sondes bd
	api.Sonde = api.bd.getSondes(nbMin, tmt)

	for e := api.Sonde.Front(); e != nil; e = e.Next() {
		sondesJSON = append(sondesJSON, e.Value.(Sonde))
	}
	err := json.NewEncoder(w).Encode(sondesJSON)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}
}

func (api *ApiAgreggateur) apiFour(w http.ResponseWriter, r *http.Request) {
	//requete pour recuperer les fours bd
	/*params := mux.Vars(r)
	nb, _ := strconv.Atoi(params["nb"])*/

}
