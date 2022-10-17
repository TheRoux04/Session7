package com.example.tp1blackjack

import retrofit2.Call
import retrofit2.http.GET

interface CardAPI {
    @GET("/getCard")
    fun getCard(): Call<Card>
}