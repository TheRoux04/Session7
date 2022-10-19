package com.example.tp1blackjack

class CardRepository {
    var cardRepo : CardAPI = Retrofit.initCard()

    suspend fun getCard(deckId : Int) : Card {
        return cardRepo.getCard(deckId)
    }
}