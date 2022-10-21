package com.example.tp1blackjack

import android.util.Log
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

    var totalCardsDeck : Int = 364


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

    fun addDealerCard(card: Card){
        setCardValue(card)
        dealerCards.value = dealerCards.value?.toList()?.plus(card)
    }

    fun addPlayerCard(card: Card){
        setCardValue(card)
        playerCards.value = playerCards.value?.toList()?.plus(card)
    }

    fun setCardValue(card: Card){
        totalCardsDeck--
        if (card.rank == "As"){
            card.value = 0
        } else if (card.rank == "Valet" || card.rank == "Reine" || card.rank == "Roi"){
            card.value = 10
        } else {
            card.value = card.rank.toInt()
        }
    }

    fun getDealerScore() : Int{
        var score = 0
        var ace = 0
        for (card in dealerCards.value!!){
            score += if (card.rank == "As"){
                if (score + 11 > 21){
                    1
                }else{
                    ace++
                    11
                }
            } else if (card.rank == "Valet" || card.rank == "Reine" || card.rank == "Roi"){
                10
            } else{
                card.value
            }
        }
        for (i in 0..ace){
            if (score > 21){
                score -= 10
            }
        }
        if (dealerCards.value!!.size <= 2){
            score -= dealerCards.value!![0].value
        }
        Log.d("Nb carte", dealerCards.value!!.size.toString())
        return score
    }

    fun getPlayerScore() : Int{
        var score = 0
        for (card in playerCards.value!!){
            score += if (card.rank == "As"){
                if (score + 11 > 21){
                    1
                }else{
                    11
                }
            } else{
                card.value
            }
        }
        //Log.d("DealerScore IN model", score.toString())
        return score
    }



}

