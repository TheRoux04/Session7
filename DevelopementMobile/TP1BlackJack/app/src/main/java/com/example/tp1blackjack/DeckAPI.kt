package com.example.tp1blackjack

import retrofit2.http.GET

interface DeckAPI {
    @GET("/getDeck/7")
    suspend fun getDeck(): Deck

}