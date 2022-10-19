package com.example.tp1blackjack

import android.annotation.SuppressLint
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.LinearLayout
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider
import com.example.tp1blackjack.Retrofit.Companion.initDeck

class MainActivity : AppCompatActivity() {
    private lateinit var viewModel: GameViewModel


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        viewModel = ViewModelProvider(this)[GameViewModel::class.java]


        viewModel.deck.observe(this) {
            viewModel.getCard().observe(this) {
                viewModel.addPlayerCard(it)
            }

            viewModel.getCard().observe(this) {
                viewModel.addDealerCard(it)
            }

            viewModel.getCard().observe(this) {
                viewModel.addPlayerCard(it)
            }

            viewModel.getCard().observe(this) {
                viewModel.addDealerCard(it)
            }

            viewModel.dealerCards.observe(this) {
                val dealerCards = findViewById<ViewGroup>(R.id.croupierLayout)
                dealerCards.removeAllViews()
                for (card in it) {
                    dealerCards.addView(getImageCard(card))
                }
            }

            viewModel.playerCards.observe(this) {
                val playerCards = findViewById<ViewGroup>(R.id.joueurLayout)
                playerCards.removeAllViews()
                for (card in it) {
                    playerCards.addView(getImageCard(card))
                }
            }
        }



    }

    fun Hit(v : View){
        viewModel.getCard().observe(this) {
            viewModel.addPlayerCard(it)
        }
    }

    fun getImageCard(card: Card) : ImageView{
        val view = ImageView(this)
        when (card.suit){
            "Coeur" -> {
                when (card.rank){
                    "Ace" -> view.setImageResource(R.drawable.diamondsace)
                    "2" -> view.setImageResource(R.drawable.diamonds2)
                    "3" -> view.setImageResource(R.drawable.diamonds3)
                    "4" -> view.setImageResource(R.drawable.diamonds4)
                    "5" -> view.setImageResource(R.drawable.diamonds5)
                    "6" -> view.setImageResource(R.drawable.diamonds6)
                    "7" -> view.setImageResource(R.drawable.diamonds7)
                    "8" -> view.setImageResource(R.drawable.diamonds8)
                    "9" -> view.setImageResource(R.drawable.diamonds9)
                    "10" -> view.setImageResource(R.drawable.diamonds10)
                    "Valet" -> view.setImageResource(R.drawable.diamondsjack)
                    "Reine" -> view.setImageResource(R.drawable.diamondsqueen)
                    "Roi" -> view.setImageResource(R.drawable.diamondsking)
                }
            }
        }
        when (card.suit){
            "Pique" -> {
                when (card.rank){
                    "Ace" -> view.setImageResource(R.drawable.spadesace)
                    "2" -> view.setImageResource(R.drawable.spades2)
                    "3" -> view.setImageResource(R.drawable.spades3)
                    "4" -> view.setImageResource(R.drawable.spades4)
                    "5" -> view.setImageResource(R.drawable.spades5)
                    "6" -> view.setImageResource(R.drawable.spades6)
                    "7" -> view.setImageResource(R.drawable.spades7)
                    "8" -> view.setImageResource(R.drawable.spades8)
                    "9" -> view.setImageResource(R.drawable.spades9)
                    "10" -> view.setImageResource(R.drawable.spades10)
                    "Valet" -> view.setImageResource(R.drawable.spadesjack)
                    "Reine" -> view.setImageResource(R.drawable.spadesqueen)
                    "Roi" -> view.setImageResource(R.drawable.spadesking)
                }
            }
        }
        when (card.suit){
            "Trèfle" -> {
                when (card.rank){
                    "Ace" -> view.setImageResource(R.drawable.clubsace)
                    "2" -> view.setImageResource(R.drawable.clubs2)
                    "3" -> view.setImageResource(R.drawable.clubs3)
                    "4" -> view.setImageResource(R.drawable.clubs4)
                    "5" -> view.setImageResource(R.drawable.clubs5)
                    "6" -> view.setImageResource(R.drawable.clubs6)
                    "7" -> view.setImageResource(R.drawable.clubs7)
                    "8" -> view.setImageResource(R.drawable.clubs8)
                    "9" -> view.setImageResource(R.drawable.clubs9)
                    "10" -> view.setImageResource(R.drawable.clubs10)
                    "Valet" -> view.setImageResource(R.drawable.clubsjack)
                    "Reine" -> view.setImageResource(R.drawable.clubsqueen)
                    "Roi" -> view.setImageResource(R.drawable.clubsking)
                }
            }
        }
        when (card.suit) {
            "Carreau" -> {
                when (card.rank) {
                    "Ace" -> view.setImageResource(R.drawable.diamondsace)
                    "2" -> view.setImageResource(R.drawable.diamonds2)
                    "3" -> view.setImageResource(R.drawable.diamonds3)
                    "4" -> view.setImageResource(R.drawable.diamonds4)
                    "5" -> view.setImageResource(R.drawable.diamonds5)
                    "6" -> view.setImageResource(R.drawable.diamonds6)
                    "7" -> view.setImageResource(R.drawable.diamonds7)
                    "8" -> view.setImageResource(R.drawable.diamonds8)
                    "9" -> view.setImageResource(R.drawable.diamonds9)
                    "10" -> view.setImageResource(R.drawable.diamonds10)
                    "Valet" -> view.setImageResource(R.drawable.diamondsjack)
                    "Reine" -> view.setImageResource(R.drawable.diamondsqueen)
                    "Roi" -> view.setImageResource(R.drawable.diamondsking)
                }
            }
        }

        //LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(104, ViewGroup.LayoutParams.WRAP_CONTENT)
        //params.weight = 1.0f;
        //view.layoutParams
        return view
    }

    fun getCard(){

    }


}



