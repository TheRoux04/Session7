package main

import (
	"encoding/json"
	"github.com/gorilla/mux"
	"net/http"
	"strconv"
)

type DogFact struct {
	Facts   string `json:"facts"`
	Success bool   `json:"success"`
}

var facts = []DogFact{
	{Facts: "Dogo"},
	{Facts: "Barf"},
}

func main() {
	routeur := mux.NewRouter()
	routeur.HandleFunc("/facts", returnAll).Methods(http.MethodGet)
	routeur.HandleFunc("/facts/{id}", returnOne).Methods(http.MethodGet)
	routeur.HandleFunc("/facts", create).Methods(http.MethodPost)
	routeur.HandleFunc("/facts/{id}", update).Methods(http.MethodPut)
	routeur.HandleFunc("/facts/{id}", delete).Methods(http.MethodDelete)
	http.ListenAndServe(":8000", routeur)

}

func returnAll(w http.ResponseWriter, r *http.Request) {
	json.NewEncoder(w).Encode(facts)
}

func returnOne(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	id, _ := strconv.Atoi(vars["id"])
	json.NewEncoder(w).Encode(facts[id])
}

// Copilot la fait toute seule donc pas sûre que cest bon
func create(w http.ResponseWriter, r *http.Request) {
	var fact DogFact
	json.NewDecoder(r.Body).Decode(&fact)
	facts = append(facts, fact)
	json.NewEncoder(w).Encode(facts)
}

func update(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	id, _ := strconv.Atoi(vars["id"])
	var fact DogFact
	json.NewDecoder(r.Body).Decode(&fact)
	facts[id] = fact
	json.NewEncoder(w).Encode(facts)
}

func delete(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	id, _ := strconv.Atoi(vars["id"])
	facts = append(facts[:id], facts[id+1:]...)
	json.NewEncoder(w).Encode(facts)
}

//
