package com.example.tp1blackjack

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import androidx.lifecycle.liveData
import kotlinx.coroutines.Dispatchers


class GameViewModel : ViewModel() {
    private val repoDeck : DeckRepository = DeckRepository()
    private val repoCard : CardRepository = CardRepository()

    var dealerCards : MutableLiveData<List<Card>> = MutableLiveData<List<Card>>()
    var playerCards : MutableLiveData<List<Card>> = MutableLiveData<List<Card>>()


    init {
        dealerCards.value = listOf()
        playerCards.value = listOf()
    }

    var deck = liveData(Dispatchers.IO) {
        val deck = repoDeck.getDeck()
        emit(deck)
    }

    fun changeDeck(){
        deck = liveData(Dispatchers.IO) {
            val deck = repoDeck.getDeck()
            emit(deck)
        }
    }

    fun getCard() =  liveData(Dispatchers.IO){
        val card = repoCard.getCard(deck.value!!.deckId)
        emit(card)

    }

    fun getDeckId() : Int{
        return deck.value!!.deckId
    }

    fun addDealerCard(card: Card){
        dealerCards.value = dealerCards.value?.toList()?.plus(card)
    }

    fun addPlayerCard(card: Card){
        playerCards.value = playerCards.value?.toList()?.plus(card)
    }



}

