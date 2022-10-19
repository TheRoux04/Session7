package com.example.tp1blackjack

import retrofit2.Call
import retrofit2.http.GET
import retrofit2.http.Path

interface CardAPI {
    @GET("/getCard/{deckId}")
    suspend fun getCard(@Path("deckId") deckId : Int): Card

}