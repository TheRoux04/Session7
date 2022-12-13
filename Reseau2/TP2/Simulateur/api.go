package main

import (
	"container/list"
	"encoding/json"
	"github.com/gorilla/mux"
	"net/http"
	"sync"
)

type ReceptionAPI struct {
	ListRecep *list.List
	Mutex     *sync.RWMutex
}

func newApiReception() *ReceptionAPI {
	return &ReceptionAPI{
		ListRecep: list.New(),
		Mutex:     &sync.RWMutex{},
	}
}

func startAPI(api *ReceptionAPI) {
	go reception(api.ListRecep, api.Mutex)
	routeur := mux.NewRouter()
	routeur.HandleFunc("/api/reception", api.receptionAPI).Methods("GET")
	http.ListenAndServe(":8080", routeur)
}

func (apiRecep *ReceptionAPI) receptionAPI(w http.ResponseWriter, r *http.Request) {
	var receptionJSON []Reception
	apiRecep.Mutex.RLock()
	for e := apiRecep.ListRecep.Front(); e != nil; e = e.Next() {
		receptionJSON = append(receptionJSON, e.Value.(Reception))
	}
	apiRecep.Mutex.RUnlock()
	err := json.NewEncoder(w).Encode(receptionJSON)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}
}
