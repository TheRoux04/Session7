package com.example.tp1blackjack

import retrofit2.Call
import retrofit2.http.GET

interface DeckAPI {
    @GET("/getDeck")
    suspend fun getDeck(): Deck

}