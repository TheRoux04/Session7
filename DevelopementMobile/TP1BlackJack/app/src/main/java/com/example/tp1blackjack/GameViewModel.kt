package com.example.tp1blackjack

import android.app.Application
import android.util.Log
import androidx.lifecycle.*
import kotlinx.coroutines.Dispatchers


class GameViewModel(application: Application) : AndroidViewModel(application) {
    private val repoDeck : DeckRepository = DeckRepository()
    private val repoCard : CardRepository = CardRepository()

    var dealerCards : MutableLiveData<List<Card>> = MutableLiveData<List<Card>>()
    var playerCards : MutableLiveData<List<Card>> = MutableLiveData<List<Card>>()
    val statsDAO = StatsDatabase.getDatabase(application).statsDAO()

    var allStats : MutableLiveData<List<Stats>> = MutableLiveData<List<Stats>>()
    //lateinit var pourcentage : List<String>

    var totalCardsDeck : Int = 364


    init {

        dealerCards.value = listOf()
        playerCards.value = listOf()
        allStats.value = listOf()

        statsDAO.initStat(Stats(1,28))
        statsDAO.initStat(Stats(2,28))
        statsDAO.initStat(Stats(3,28))
        statsDAO.initStat(Stats(4,28))
        statsDAO.initStat(Stats(5,28))
        statsDAO.initStat(Stats(6,28))
        statsDAO.initStat(Stats(7,28))
        statsDAO.initStat(Stats(8,28))
        statsDAO.initStat(Stats(9,28))
        statsDAO.initStat(Stats(10,112))
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
        //statsDAO.updateStats(card.value)
        setCardValue(card)
        dealerCards.value = dealerCards.value?.toList()?.plus(card)
        //displayStats()
    }

    fun addPlayerCard(card: Card){
        //statsDAO.updateStats(card.value)
        setCardValue(card)
        playerCards.value = playerCards.value?.toList()?.plus(card)
        //displayStats()
    }

    fun setCardValue(card: Card){
        totalCardsDeck--
        if (card.rank == "As"){
            card.value = 1
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


    fun initStats()  {
        statsDAO.deleteStats()
    }

    fun displayStats() : LiveData<List<Stats>> {
        allStats.value = statsDAO.getAll()

        /*for (stat in allStats.value!!){
            //pourcentage.plus((stat.leftCard.toDouble() / totalCardsDeck.toDouble() * 100).toString().take(4) + "%")
        }*/

        return allStats
    }

    /*fun getPourcentage() : LiveData<List<String>> {
        return MutableLiveData(pourcentage)
    }*/
}
