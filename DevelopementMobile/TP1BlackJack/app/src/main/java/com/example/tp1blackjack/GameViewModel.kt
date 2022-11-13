package com.example.tp1blackjack

import android.app.Application

import androidx.lifecycle.*
import kotlinx.coroutines.Dispatchers


class GameViewModel(application: Application) : AndroidViewModel(application) {
    private val repoDeck : DeckRepository = DeckRepository()
    private val repoCard : CardRepository = CardRepository()

    var dealerCards : MutableLiveData<List<Card>> = MutableLiveData<List<Card>>()
    var playerCards : MutableLiveData<List<Card>> = MutableLiveData<List<Card>>()
    val statsDAO = StatsDatabase.getDatabase(application).statsDAO()
    var allStats : MutableLiveData<List<Stats>> = MutableLiveData<List<Stats>>()
    var pourcentage : List<String>
    var totalCardsDeck : Int = 364
    val bet = MutableLiveData<Int>()
    val bank = MutableLiveData<Int>()
    val messageGame = MutableLiveData<String>()
    var cardFaceDown : MutableLiveData<Card> = MutableLiveData<Card>()
    var startGame = MutableLiveData<Boolean>()
    var pourcentageLeft = MutableLiveData<String>()

    init {
        dealerCards.value = listOf()
        playerCards.value = listOf()
        allStats.value = listOf()
        pourcentage = listOf()
        bank.value = 1000
        messageGame.value = "Welcome to Blackjack, place your bet"

        statsDAO.deleteStats()
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
        setCardValue(card)
        if (dealerCards.value!!.isEmpty()){
            cardFaceDown.value = card
        }
        else{
            statsDAO.updateStats(card.value)
        }
        dealerCards.value = dealerCards.value?.toList()?.plus(card)
        displayStats()
    }

    fun addPlayerCard(card: Card){
        setCardValue(card)
        playerCards.value = playerCards.value?.toList()?.plus(card)
        statsDAO.updateStats(card.value)
        displayStats()
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

    fun getDealerScore(realScore : Boolean = false) : Int{
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
            if (score > 21 && ace > 0){
                score -= 10
            }
        }
        if (dealerCards.value!!.size <= 2 && !realScore){
            score -= dealerCards.value!![0].value
        }

        return score
    }

    fun getPlayerScore() : Int{
        var score = 0
        var ace = 0
        for (card in playerCards.value!!){
            score += if (card.rank == "As"){
                if (score + 11 > 21){
                    1
                }else{
                    ace++
                    11
                }
            } else{
                card.value
            }
        }
        for (i in 0..ace){
            if (score > 21 && ace > 0){
                score -= 10
            }
        }
        return score
    }

    fun displayStats() : LiveData<List<Stats>> {
		allStats.value = statsDAO.getAll()
        return allStats
    }

    fun getPourcentage() : LiveData<List<String>> {
        return MutableLiveData(pourcentage)
    }

    fun changeBankAmountWin(win : Int){
        if (win == 21){
            bank.value = bank.value?.plus(bet.value!! * 2)
            messageGame.value = "Blackjack ! You win ${bet.value!! * 2} $"
        }
        if (win == 1){
            bank.value = bank.value?.plus(bet.value!! * 2)
            messageGame.value = "You win! You won ${bet.value!! * 2} $ Please place your next bet"
        } else if (win == 0){
            messageGame.value = "Dealer win! You lost ${bet.value!!}$ Please place a new bet"
        } else {
            bank.value = bank.value?.plus(bet.value!!)
            messageGame.value = "Tie ! You got ${bet.value!!}$ back! Please place a new bet"
        }
        startGame.value = false
    }

    fun updateFaceDownCard(){
        statsDAO.updateStats(cardFaceDown.value!!.value)
        getPourcentage()
        displayStats()
    }

    fun start(){
        startGame.value = true
    }

}

