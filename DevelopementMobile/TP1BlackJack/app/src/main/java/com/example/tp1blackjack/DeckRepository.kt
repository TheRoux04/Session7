package com.example.tp1blackjack;

class DeckRepository {
    var deck: DeckAPI = Retrofit.initDeck()
    suspend fun getDeck() = deck.getDeck()
}
