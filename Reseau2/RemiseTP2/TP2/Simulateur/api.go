package main

import (
	"container/list"
	"encoding/json"
	"github.com/gorilla/mux"
	"net/http"
	"sync"
)

type API struct {
	ReceptionList *list.List
	Mutex         *sync.RWMutex
}

func newRecepAPI() *API {
	return &API{
		ReceptionList: list.New(),
		Mutex:         &sync.RWMutex{},
	}
}

func APIStart(api *API) {
	routeur := mux.NewRouter()
	routeur.HandleFunc("/api/reception", api.recepApi).Methods("GET")
	http.ListenAndServe(":8089", routeur)
}

func (api *API) recepApi(w http.ResponseWriter, r *http.Request) {
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
