package com.example.tp1blackjack

import androidx.lifecycle.ViewModel
import androidx.lifecycle.liveData
import kotlinx.coroutines.Dispatchers


class GameViewModel : ViewModel() {
    private val repoDeck : DeckRepository = DeckRepository()
    //private val repoCard : CardRepository = CardRepository()

    val deck = liveData(Dispatchers.IO) {
        val deck = repoDeck.getDeck()
        emit(deck)
    }

}

