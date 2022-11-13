package com.example.tp1blackjack

import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory

class Retrofit {
    companion object {
        fun initDeck(): DeckAPI {
            return Retrofit.Builder()
                .baseUrl("https://c56.drynish.synology.me")
                .addConverterFactory(GsonConverterFactory.create())
                .build().create(DeckAPI::class.java)
        }

        fun initCard(): CardAPI {
            return Retrofit.Builder()
                .baseUrl("https://c56.drynish.synology.me")
                .addConverterFactory(GsonConverterFactory.create())
                .build().create(CardAPI::class.java)
        }
    }
}

