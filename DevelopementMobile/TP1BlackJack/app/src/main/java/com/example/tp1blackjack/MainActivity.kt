package com.example.tp1blackjack

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.ImageView
import com.example.tp1blackjack.Retrofit.Companion.initDeck

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val view = ImageView(this)
        //view.setImageResource(R.drawable.jeu_carte_1280x715) fond d ecran

        val retrofit = initDeck()
        var deckCall = retrofit.getDeck()



    }

    fun getImageCard(card: Card) : ImageView{
        val view = ImageView(this)
        when (card.suit == "Carreau"){
            card.rank == "Ace" -> view.setImageResource(R.drawable.diamondsace)
            card.rank == "2" -> view.setImageResource(R.drawable.diamonds2)
            card.rank == "3" -> view.setImageResource(R.drawable.diamonds3)
            card.rank == "4" -> view.setImageResource(R.drawable.diamonds4)
            card.rank == "5" -> view.setImageResource(R.drawable.diamonds5)
            card.rank == "6" -> view.setImageResource(R.drawable.diamonds6)
            card.rank == "7" -> view.setImageResource(R.drawable.diamonds7)
            card.rank == "8" -> view.setImageResource(R.drawable.diamonds8)
            card.rank == "9" -> view.setImageResource(R.drawable.diamonds9)
            card.rank == "10" -> view.setImageResource(R.drawable.diamonds10)
            card.rank == "Valet" -> view.setImageResource(R.drawable.diamondsjack)
            card.rank == "Reine" -> view.setImageResource(R.drawable.diamondsqueen)
            card.rank == "Roi" -> view.setImageResource(R.drawable.diamondsking)
            else -> {}
        }
        when (card.suit == "Coeur"){
            card.rank == "Ace" -> view.setImageResource(R.drawable.heartsace)
            card.rank == "2" -> view.setImageResource(R.drawable.hearts2)
            card.rank == "3" -> view.setImageResource(R.drawable.hearts3)
            card.rank == "4" -> view.setImageResource(R.drawable.hearts4)
            card.rank == "5" -> view.setImageResource(R.drawable.hearts5)
            card.rank == "6" -> view.setImageResource(R.drawable.hearts6)
            card.rank == "7" -> view.setImageResource(R.drawable.hearts7)
            card.rank == "8" -> view.setImageResource(R.drawable.hearts8)
            card.rank == "9" -> view.setImageResource(R.drawable.hearts9)
            card.rank == "10" -> view.setImageResource(R.drawable.hearts10)
            card.rank == "Valet" -> view.setImageResource(R.drawable.heartsjack)
            card.rank == "Reine" -> view.setImageResource(R.drawable.heartsqueen)
            card.rank == "Roi" -> view.setImageResource(R.drawable.heartsking)
            else -> {}
        }
        when (card.suit == "Pique"){
            card.rank == "Ace" -> view.setImageResource(R.drawable.spadesace)
            card.rank == "2" -> view.setImageResource(R.drawable.spades2)
            card.rank == "3" -> view.setImageResource(R.drawable.spades3)
            card.rank == "4" -> view.setImageResource(R.drawable.spades4)
            card.rank == "5" -> view.setImageResource(R.drawable.spades5)
            card.rank == "6" -> view.setImageResource(R.drawable.spades6)
            card.rank == "7" -> view.setImageResource(R.drawable.spades7)
            card.rank == "8" -> view.setImageResource(R.drawable.spades8)
            card.rank == "9" -> view.setImageResource(R.drawable.spades9)
            card.rank == "10" -> view.setImageResource(R.drawable.spades10)
            card.rank == "Valet" -> view.setImageResource(R.drawable.spadesjack)
            card.rank == "Reine" -> view.setImageResource(R.drawable.spadesqueen)
            card.rank == "Roi" -> view.setImageResource(R.drawable.spadesking)
            else -> {}
        }
        when (card.suit == "Trèfle") {
            card.rank == "Ace" -> view.setImageResource(R.drawable.clubsace)
            card.rank == "2" -> view.setImageResource(R.drawable.clubs2)
            card.rank == "3" -> view.setImageResource(R.drawable.clubs3)
            card.rank == "4" -> view.setImageResource(R.drawable.clubs4)
            card.rank == "5" -> view.setImageResource(R.drawable.clubs5)
            card.rank == "6" -> view.setImageResource(R.drawable.clubs6)
            card.rank == "7" -> view.setImageResource(R.drawable.clubs7)
            card.rank == "8" -> view.setImageResource(R.drawable.clubs8)
            card.rank == "9" -> view.setImageResource(R.drawable.clubs9)
            card.rank == "10" -> view.setImageResource(R.drawable.clubs10)
            card.rank == "Valet" -> view.setImageResource(R.drawable.clubsjack)
            card.rank == "Reine" -> view.setImageResource(R.drawable.clubsqueen)
            card.rank == "Roi" -> view.setImageResource(R.drawable.clubsking)
            else -> {}
        }

        view.layoutParams.height = 225
        return view
    }

    fun getCard(){

    }
}



