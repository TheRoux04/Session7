package com.example.examen1

import android.graphics.Color
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.CountDownTimer
import android.os.Handler
import android.os.Looper
import android.util.Log
import android.view.View
import android.widget.Button
import android.widget.TextView
import androidx.lifecycle.ViewModelProvider
import java.util.*

class MainActivity : AppCompatActivity() {
    private lateinit var viewModel: GameViewModel
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        viewModel = ViewModelProvider(this)[GameViewModel::class.java]

        var message = findViewById<TextView>(R.id.txtMessage)
        var buttonGreen = findViewById<Button>(R.id.btn1)
        var buttonRed = findViewById<Button>(R.id.btn2)
        var buttonYellow = findViewById<Button>(R.id.btn3)
        var buttonBlue = findViewById<Button>(R.id.btn4)
        buttonGreen.setBackgroundColor(Color.rgb(26, 103, 29))
        buttonRed.setBackgroundColor(Color.rgb(112, 16, 16))
        buttonYellow.setBackgroundColor(Color.rgb(138, 126, 17))
        buttonBlue.setBackgroundColor(Color.rgb(26, 39, 120))

        buttonGreen.setOnClickListener {
            Log.d("Click", "GREEN")
            viewModel.addSequenceUser(1)
        }

        buttonRed.setOnClickListener {
            Log.d("Click", "RED")
            viewModel.addSequenceUser(2)
        }

        buttonYellow.setOnClickListener {
            Log.d("Click", "YELLOW")
            viewModel.addSequenceUser(3)
        }

        buttonBlue.setOnClickListener {
            Log.d("Click", "BLUE")
            viewModel.addSequenceUser(4)
        }

        viewModel.lightButton.observe(this){
            Log.d("Id", it.toString())
            when(it){
                1 -> {
                    buttonGreen.setBackgroundColor(Color.GREEN)
                    viewModel.addSequenceSolution(1)
                    Handler(Looper.getMainLooper()).postDelayed({
                        buttonGreen.setBackgroundColor(Color.rgb(26, 103, 29))
                    }, 1000)

                }
                2 -> {
                    buttonRed.setBackgroundColor(Color.RED)
                    viewModel.addSequenceSolution(2)
                    Handler(Looper.getMainLooper()).postDelayed({
                        buttonRed.setBackgroundColor(Color.rgb(112, 16, 16))
                    }, 1000)
                }
                3 -> {
                    buttonYellow.setBackgroundColor(Color.YELLOW)
                    viewModel.addSequenceSolution(3)
                    Handler(Looper.getMainLooper()).postDelayed({
                        buttonYellow.setBackgroundColor(Color.rgb(138, 126, 17))
                    }, 1000)
                }
                4 -> {
                    buttonBlue.setBackgroundColor(Color.BLUE)
                    viewModel.addSequenceSolution(4)
                    Handler(Looper.getMainLooper()).postDelayed({
                        buttonBlue.setBackgroundColor(Color.rgb(26, 39, 120))
                    }, 1000)
                }
            }
        }

        viewModel.finished.observe(this){
            if (it){
                buttonGreen.isClickable = true
                buttonRed.isClickable = true
                buttonYellow.isClickable = true
                buttonBlue.isClickable = true
            } else {
                buttonGreen.isClickable = false
                buttonRed.isClickable = false
                buttonYellow.isClickable = false
                buttonBlue.isClickable = false
            }
        }

        viewModel.error.observe(this){
            if (it){
                buttonGreen.isClickable = false
                buttonRed.isClickable = false
                buttonYellow.isClickable = false
                buttonBlue.isClickable = false
                message.text = viewModel.message.value.toString()
            }
        }

        viewModel.won.observe(this){
            if (it){
                buttonGreen.isClickable = false
                buttonRed.isClickable = false
                buttonYellow.isClickable = false
                buttonBlue.isClickable = false
                message.text = viewModel.message.value.toString()
            }
        }

    }

    fun startSequence(v : View){
        viewModel.initiateSequence(4)
    }



}