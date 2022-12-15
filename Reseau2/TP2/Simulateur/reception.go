package main

import (
	"container/list"
	"fmt"
	"math/rand"
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

func receptionMain() {
	api := newApiReception()
	go reception(api.ReceptionList, api.Mutex)
	startApi(api)

}

func newReception(id int) Reception {
	var timestamp = time.Now().Format("2006-01-02 15:04:05")
	newRecep := Reception{
		Timestamp:  timestamp,
		CommandeId: id,
		TotalPig:   rand.Intn(50),
		Pig:        rand.Intn(50),
		Piggy:      rand.Intn(50),
		Pigget:     rand.Intn(50),
	}
	newRecep.TotalPig = newRecep.Pig + newRecep.Piggy + newRecep.Pigget
	return newRecep
}

func reception(listRecep *list.List, m *sync.RWMutex) {
	ticker := time.NewTicker(time.Minute)
	fmt.Println("STARTING SIMULATION OF RECEPTION")
	idCom := 0
	for {
		idCom++
		getReception(listRecep, m, idCom)
		<-ticker.C
	}
}

func getReception(listRecep *list.List, m *sync.RWMutex, idCom int) {
	m.Lock()
	if listRecep.Len() >= 10 {
		listRecep.Remove(listRecep.Front())
	}
	listRecep.PushBack(newReception(idCom))
	m.Unlock()
}
