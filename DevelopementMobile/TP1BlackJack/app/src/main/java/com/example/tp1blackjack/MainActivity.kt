package com.example.tp1blackjack

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

        stats.visibility = View.GONE
        startNewHands()

    }

    fun startNewHands(){

        var firstHand: Boolean = true
        val txtDealerScore = findViewById<TextView>(R.id.dealerScore)
        val txtPlayerScore = findViewById<TextView>(R.id.playerScore)
        val playerCards = findViewById<ViewGroup>(R.id.playerLayout)
        val dealerCards = findViewById<ViewGroup>(R.id.dealerLayout)
        val btnHit = findViewById<View>(R.id.btnHit)
        val btnStand = findViewById<View>(R.id.btnStand)
        viewModel = ViewModelProvider(this)[GameViewModel::class.java]
        dealerCards.removeAllViews()
        playerCards.removeAllViews()
        txtDealerScore.text = "0"
        txtPlayerScore.text = "0"

        if (viewModel.totalCardsDeck < 20){
            viewModel.changeDeck()
        }

        viewModel.deck.observe(this) {
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
                                    startNewHands()
                                }, 2000)
                            }
                        }
                    }
                }
            }
        }

        viewModel.dealerCards.observe(this) {
            btnHit.isEnabled = false
            btnStand.isEnabled = false
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
            btnHit.isEnabled = true
            btnStand.isEnabled = true
        }

        viewModel.playerCards.observe(this) {
            btnHit.isEnabled = false
            btnStand.isEnabled = false
            playerCards.removeAllViews()
            for (card in it) {
                playerCards.addView(getImageCard(card, false))
                txtPlayerScore.text = viewModel.getPlayerScore().toString()
                //Log.d("Player", card.rank + " " + card.suit)
            }
            btnHit.isEnabled = true
            btnStand.isEnabled = true
        }

        /*viewModel.displayStats().observe(this) {
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

            }
            /*
            viewModel.getPourcentage().observe(this) {
                for (pourcentage in it) {
                    val txtChances = TextView(this)
                    chancesLay.addView(txtChances.apply {
                        text = pourcentage
                        textSize = 24f
                        setTextColor(Color.BLACK)
                        setBackgroundColor(Color.parseColor("#4CAF50"))
                        gravity = Gravity.CENTER
                    })
                }
            }*/

            totalCard.text = viewModel.totalCardsDeck.toString()
        }*/

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
                btnHit.isEnabled = false
                btnStand.isEnabled = false
                Log.d("Player", "Bust")
                Log.d("Dealer", "Win")
                for (card in dealCards) {
                    dealerCards.addView(getImageCard(card, false))
                    txtDealerScore.text = viewModel.getDealerScore().toString()
                }
                Handler(Looper.getMainLooper()).postDelayed({
                    startNewHands()
                }, 2000)

            } else if (viewModel.getPlayerScore() == 21){
                Handler(Looper.getMainLooper()).postDelayed({
                    startNewHands()
                }, 2000)
            }
        }
    }

    fun Stand(v : View){
        val btnHit = findViewById<View>(R.id.btnHit)
        val btnStand = findViewById<View>(R.id.btnStand)
        btnHit.isEnabled = false
        btnStand.isEnabled = false
        if(viewModel.getDealerScore() < 17 && viewModel.getDealerScore() < viewModel.getPlayerScore()){
            viewModel.getCard().observe(this) {
                viewModel.addDealerCard(it)
                if (viewModel.getDealerScore() > 21){
                    Log.d("Dealer", "Bust")
                    Log.d("Player", "Win")
                    Handler(Looper.getMainLooper()).postDelayed({
                        startNewHands()
                    }, 2000)
                }else if (viewModel.getDealerScore() < 17 && viewModel.getDealerScore() < viewModel.getPlayerScore()){
                    Handler(Looper.getMainLooper()).postDelayed({
                        Stand(v)
                    }, 1000)

                } else if (viewModel.getDealerScore() > 16 && viewModel.getDealerScore() > viewModel.getPlayerScore()){
                    Log.d("Dealer", "Win")
                    Handler(Looper.getMainLooper()).postDelayed({
                        startNewHands()
                    }, 2000)
                } else if (viewModel.getDealerScore() == viewModel.getPlayerScore()){
                    Log.d("Dealer", "Tie")
                    Handler(Looper.getMainLooper()).postDelayed({
                        startNewHands()
                    }, 2000)
                } else {
                    Log.d("Player", "Win")
                    Handler(Looper.getMainLooper()).postDelayed({
                        startNewHands()
                    }, 2000)
                }
            }
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
                            view.setBackgroundColor(Color.rgb(255, 255, 255));
                        }
                        "Reine" -> {
                            view.setImageResource(R.drawable.diamondsqueen)
                            view.setBackgroundColor(Color.rgb(255, 255, 255));
                        }
                        "Roi" -> {
                            view.setImageResource(R.drawable.diamondsking)
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



