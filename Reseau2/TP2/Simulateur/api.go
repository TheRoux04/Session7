package main

import (
	"container/list"
	"encoding/json"
	"github.com/gorilla/mux"
	"net/http"
	"sync"
)

type ApiReception struct {
	ReceptionList *list.List
	Mutex         *sync.RWMutex
}

func newApiReception() *ApiReception {
	return &ApiReception{
		ReceptionList: list.New(),
		Mutex:         &sync.RWMutex{},
	}
}

func (api *ApiReception) apiReception(w http.ResponseWriter, r *http.Request) {
	var receptionJSON []Reception
	api.Mutex.RLock()
	for e := api.ReceptionList.Front(); e != nil; e = e.Next() {
		receptionJSON = append(receptionJSON, e.Value.(Reception))
	}
	api.Mutex.RUnlock()
	err := json.NewEncoder(w).Encode(receptionJSON)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}
}

func startApi(api *ApiReception) {
	routeur := mux.NewRouter()
	routeur.HandleFunc("/api/reception", api.apiReception).Methods("GET")
	http.ListenAndServe(":8083", routeur)
}
