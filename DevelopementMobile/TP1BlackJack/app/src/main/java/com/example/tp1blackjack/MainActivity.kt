package com.example.tp1blackjack

import android.annotation.SuppressLint
import android.graphics.Color
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.util.Log
import android.view.Gravity
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.LinearLayout
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.ViewModelProvider
import com.google.android.material.navigation.NavigationView


class MainActivity : AppCompatActivity() {
    private lateinit var viewModel: GameViewModel


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val stats = findViewById<NavigationView>(R.id.stats)

        viewModel = ViewModelProvider(this)[GameViewModel::class.java]

        viewModel.deck.observe(this) {
            Log.d("deck", it.toString())
        }

        showBet()

        stats.visibility = View.GONE

        viewModel.startGame.observe(this) {
            if (it) {
                startNewHands()
            }
        }
    }

    fun showBet(){
        FragmentBet().show(supportFragmentManager, "fragment_bet")
    }

    @SuppressLint("SetTextI18n")
    fun startNewHands(){

        var firstHand: Boolean = true
        val txtDealerScore = findViewById<TextView>(R.id.dealerScore)
        val txtPlayerScore = findViewById<TextView>(R.id.playerScore)
        val playerCards = findViewById<ViewGroup>(R.id.playerLayout)
        val dealerCards = findViewById<ViewGroup>(R.id.dealerLayout)
        val btnHit = findViewById<View>(R.id.btnHit)
        val btnStand = findViewById<View>(R.id.btnStand)
        val txtMainBet = findViewById<TextView>(R.id.txtMainBet)
        val txtBank = findViewById<TextView>(R.id.txtBank)

        viewModel.dealerCards.value = listOf()
        viewModel.playerCards.value = listOf()
        dealerCards.removeAllViews()
        playerCards.removeAllViews()
        btnHit.isEnabled = false
        btnStand.isEnabled = false
        txtDealerScore.text = "0"
        txtPlayerScore.text = "0"
        txtMainBet.text = "Bet: ${viewModel.bet.value}"

        if (viewModel.totalCardsDeck < 20){
            viewModel.changeDeck()
        }

        viewModel.bank.observe(this){
            txtBank.text = "Bank: $it"
        }

        viewModel.getCard().observe(this) {
            viewModel.addPlayerCard(it)
            viewModel.getCard().observe(this) {
                viewModel.addDealerCard(it)
                viewModel.getCard().observe(this) {
                    viewModel.addPlayerCard(it)
                    viewModel.getCard().observe(this) {
                        viewModel.addDealerCard(it)
                        if (viewModel.getPlayerScore() == 21){
                            Log.d("Player", "Blackjack")
                            Log.d("Dealer", "Lose")
                            Handler(Looper.getMainLooper()).postDelayed({
                                btnHit.isEnabled = false
                                btnStand.isEnabled = false
                                viewModel.changeBankAmountWin(21)
                                showBet()
                            }, 2000)
                        } else{
                            btnHit.isEnabled = true
                            btnStand.isEnabled = true
                        }
                    }
                }
            }
        }

        viewModel.dealerCards.observe(this) {
            dealerCards.removeAllViews()
            if (it.size <= 2 && viewModel.getPlayerScore() != 21){
                firstHand = true
            }
            for (card in it) {
                dealerCards.addView(getImageCard(card, firstHand))
                txtDealerScore.text = viewModel.getDealerScore().toString()
                Log.d("Dealer", viewModel.getDealerScore().toString())
                firstHand = false
            }
        }

        viewModel.playerCards.observe(this) {
            playerCards.removeAllViews()
            for (card in it) {
                playerCards.addView(getImageCard(card, false))
                txtPlayerScore.text = viewModel.getPlayerScore().toString()
                //Log.d("Player", card.rank + " " + card.suit)
            }
        }

        viewModel.displayStats().observe(this) { it ->
            val cardLeftLay = findViewById<LinearLayout>(R.id.cardLeftLayout)
            val chancesLay = findViewById<LinearLayout>(R.id.chancesLayout)
            val totalCard = findViewById<TextView>(R.id.txtCardsLeft)

            cardLeftLay.removeAllViews()
            chancesLay.removeAllViews()
            for (stat in it) {
                val txtCardLeft = TextView(this)
                cardLeftLay.addView(txtCardLeft.apply {
                    text = stat.leftCard.toString()
                    textSize = 24f
                    setTextColor(Color.BLACK)
                    setBackgroundColor(Color.parseColor("#4CAF50"))
                    gravity = Gravity.CENTER
                })

                val txtChances = TextView(this)
                chancesLay.addView(txtChances.apply {
                    text = ((stat.leftCard.toDouble() / 364.0) * 100).toString().take(4) + "%"
                    Log.d("left card", stat.leftCard.toString())
                    Log.d("total", viewModel.totalCardsDeck.toString())
                    Log.d("divisé", ((stat.leftCard.toDouble() / viewModel.totalCardsDeck.toDouble())).toString())
                    Log.d("fois 100", ((stat.leftCard.toDouble() / viewModel.totalCardsDeck.toDouble()) * 100).toString())

                    textSize = 24f
                    setTextColor(Color.BLACK)
                    setBackgroundColor(Color.parseColor("#4CAF50"))
                    gravity = Gravity.CENTER
                })
            }
            totalCard.text = viewModel.totalCardsDeck.toString()
        }
    }

    fun OpenStats(view: View){
        val stats = findViewById<NavigationView>(R.id.stats)

        if (stats.visibility == View.VISIBLE){
            stats.visibility = View.GONE
        }else{
            stats.visibility = View.VISIBLE
        }
    }

    fun Hit(v : View){
        val dealerCards = findViewById<ViewGroup>(R.id.dealerLayout)
        val txtDealerScore = findViewById<TextView>(R.id.dealerScore)
        val btnHit = findViewById<View>(R.id.btnHit)
        val btnStand = findViewById<View>(R.id.btnStand)
        val dealCards = viewModel.dealerCards.value!!

        btnHit.isEnabled = false
        btnStand.isEnabled = false

        viewModel.getCard().observe(this) {
            viewModel.addPlayerCard(it)
            if (viewModel.getPlayerScore() > 21){
                Log.d("Player", "Bust")
                Log.d("Dealer", "Win")
                dealerCards.removeViewAt(0)
                dealerCards.addView(getImageCard(dealCards[0], false))
                txtDealerScore.text = viewModel.getDealerScore(true).toString()
                viewModel.updateFaceDownCard()
                viewModel.changeBankAmountWin(0)
                Handler(Looper.getMainLooper()).postDelayed({
                    showBet()
                }, 2000)
            } else {
                btnHit.isEnabled = true
                btnStand.isEnabled = true
            }
        }
    }

    fun Stand(v : View){
        val dealerCards = findViewById<ViewGroup>(R.id.dealerLayout)
        val dealCards = viewModel.dealerCards.value!!
        val txtDealerScore = findViewById<TextView>(R.id.dealerScore)
        val btnHit = findViewById<View>(R.id.btnHit)
        val btnStand = findViewById<View>(R.id.btnStand)
        btnHit.isEnabled = false
        btnStand.isEnabled = false
        if(viewModel.getDealerScore() < 17){
            viewModel.getCard().observe(this) {
                viewModel.addDealerCard(it)
                if (viewModel.getDealerScore() > 21){
                    Log.d("Dealer", "Bust")
                    Log.d("Player", "Win")
                    viewModel.changeBankAmountWin(1)
                    Handler(Looper.getMainLooper()).postDelayed({
                        showBet()
                    }, 2000)
                }else if (viewModel.getDealerScore() < 17 && viewModel.getDealerScore() < viewModel.getPlayerScore()){
                    Handler(Looper.getMainLooper()).postDelayed({
                        Stand(v)
                    }, 2000)

                } else if (viewModel.getDealerScore() > 16 && viewModel.getDealerScore() > viewModel.getPlayerScore()){
                    Log.d("Dealer", "Win")
                    viewModel.changeBankAmountWin(0)
                    Handler(Looper.getMainLooper()).postDelayed({
                        showBet()
                    }, 2000)
                } else if (viewModel.getDealerScore() == viewModel.getPlayerScore()){
                    Log.d("Dealer", "Tie")
                    viewModel.changeBankAmountWin(2)
                    Handler(Looper.getMainLooper()).postDelayed({
                        showBet()
                    }, 2000)
                } else {
                    Log.d("Player", "Win")
                    viewModel.changeBankAmountWin(1)
                    Handler(Looper.getMainLooper()).postDelayed({
                        showBet()
                    }, 2000)
                }
            }
        } else {
            dealerCards.removeViewAt(0)
            dealerCards.addView(getImageCard(dealCards[0], false))
            txtDealerScore.text = viewModel.getDealerScore(true).toString()
            viewModel.updateFaceDownCard()
            Handler(Looper.getMainLooper()).postDelayed({
                showBet()
            }, 2000)
        }
    }

    fun getImageCard(card: Card, cardDealer: Boolean) : ImageView{
        val view = ImageView(this)

        if(cardDealer) {
            view.setImageResource(R.drawable.back)
            view.setBackgroundColor(Color.rgb(255, 255, 255));
        } else {
            when (card.suit){
                "Coeur" -> {
                    when (card.rank){
                        "As" -> {
                            view.setImageResource(R.drawable.heartsace)
                            view.setBackgroundColor(Color.rgb(255, 255, 255));
                        }
                        "2" -> view.setImageResource(R.drawable.hearts2)
                        "3" -> view.setImageResource(R.drawable.hearts3)
                        "4" -> view.setImageResource(R.drawable.hearts4)
                        "5" -> view.setImageResource(R.drawable.hearts5)
                        "6" -> view.setImageResource(R.drawable.hearts6)
                        "7" -> view.setImageResource(R.drawable.hearts7)
                        "8" -> view.setImageResource(R.drawable.hearts8)
                        "9" -> view.setImageResource(R.drawable.hearts9)
                        "10" -> view.setImageResource(R.drawable.hearts10)
                        "Valet" -> {
                            view.setImageResource(R.drawable.heartsjack)
                            view.setBackgroundColor(Color.rgb(255, 255, 255));
                        }
                        "Reine" -> {
                            view.setImageResource(R.drawable.heartsqueen)
                            view.setBackgroundColor(Color.rgb(255, 255, 255));
                        }
                        "Roi" -> {
                            view.setImageResource(R.drawable.heartsking)
                            view.setBackgroundColor(Color.rgb(255, 255, 255));
                        }
                    }
                }
            }
            when (card.suit){
                "Pique" -> {
                    when (card.rank){
                        "As" -> {
                            view.setImageResource(R.drawable.spadesace)
                            view.setBackgroundColor(Color.rgb(255, 255, 255));
                        }
                        "2" -> view.setImageResource(R.drawable.spades2)
                        "3" -> view.setImageResource(R.drawable.spades3)
                        "4" -> view.setImageResource(R.drawable.spades4)
                        "5" -> view.setImageResource(R.drawable.spades5)
                        "6" -> view.setImageResource(R.drawable.spades6)
                        "7" -> view.setImageResource(R.drawable.spades7)
                        "8" -> view.setImageResource(R.drawable.spades8)
                        "9" -> view.setImageResource(R.drawable.spades9)
                        "10" -> view.setImageResource(R.drawable.spades10)
                        "Valet" -> {
                            view.setImageResource(R.drawable.spadesjack)
                            view.setBackgroundColor(Color.rgb(255, 255, 255));
                        }
                        "Reine" -> {
                            view.setImageResource(R.drawable.spadesqueen)
                            view.setBackgroundColor(Color.rgb(255, 255, 255));
                        }
                        "Roi" -> {
                            view.setImageResource(R.drawable.spadesking)
                            view.setBackgroundColor(Color.rgb(255, 255, 255));
                        }
                    }
                }
            }
            when (card.suit){
                "Trefle" -> {
                    when (card.rank){
                        "As" -> {
                            view.setImageResource(R.drawable.clubsace)
                            view.setBackgroundColor(Color.rgb(255, 255, 255));
                        }
                        "2" -> view.setImageResource(R.drawable.clubs2)
                        "3" -> view.setImageResource(R.drawable.clubs3)
                        "4" -> view.setImageResource(R.drawable.clubs4)
                        "5" -> view.setImageResource(R.drawable.clubs5)
                        "6" -> view.setImageResource(R.drawable.clubs6)
                        "7" -> view.setImageResource(R.drawable.clubs7)
                        "8" -> view.setImageResource(R.drawable.clubs8)
                        "9" -> view.setImageResource(R.drawable.clubs9)
                        "10" -> view.setImageResource(R.drawable.clubs10)
                        "Valet" -> {
                            view.setImageResource(R.drawable.clubsjack)
                            view.setBackgroundColor(Color.rgb(255, 255, 255));
                        }
                        "Reine" -> {
                            view.setImageResource(R.drawable.clubsqueen)
                            view.setBackgroundColor(Color.rgb(255, 255, 255));
                        }
                        "Roi" -> {
                            view.setImageResource(R.drawable.clubsking)
                            view.setBackgroundColor(Color.rgb(255, 255, 255));
                        }
                    }
                }
            }
            when (card.suit) {
                "Carreau" -> {
                    when (card.rank) {
                        "As" -> {
                            view.setImageResource(R.drawable.diamondsace)
                            view.setBackgroundColor(Color.rgb(255, 255, 255));
                        }
                        "2" -> view.setImageResource(R.drawable.diamonds2)
                        "3" -> view.setImageResource(R.drawable.diamonds3)
                        "4" -> view.setImageResource(R.drawable.diamonds4)
                        "5" -> view.setImageResource(R.drawable.diamonds5)
                        "6" -> view.setImageResource(R.drawable.diamonds6)
                        "7" -> view.setImageResource(R.drawable.diamonds7)
                        "8" -> view.setImageResource(R.drawable.diamonds8)
                        "9" -> view.setImageResource(R.drawable.diamonds9)
                        "10" -> view.setImageResource(R.drawable.diamonds10)
                        "Valet" -> {
                            view.setImageResource(R.drawable.diamondsjack)
                            view.setBackgroundColor(Color.rgb(255, 255, 255))
                        }
                        "Reine" -> {
                            view.setImageResource(R.drawable.diamondsqueen)
                            view.setBackgroundColor(Color.rgb(255, 255, 255))
                        }
                        "Roi" -> {
                            view.setImageResource(R.drawable.diamondsking)
                            view.setBackgroundColor(Color.rgb(255, 255, 255))
                        }
                    }
                }
            }
        }

        view.layoutParams = ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT)
        view.adjustViewBounds = true
        return view
    }

}



