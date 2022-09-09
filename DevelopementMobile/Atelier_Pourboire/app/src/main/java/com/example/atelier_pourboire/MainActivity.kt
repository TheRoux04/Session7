package com.example.atelier_pourboire

import android.annotation.SuppressLint
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.*

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        var montant = findViewById<EditText>(R.id.editTextNumber_price)
        var toggle = findViewById<ToggleButton>(R.id.toggleButton_taxes)
        var pourcentage = findViewById<Spinner>(R.id.spinner_pourcentage)
        var people = findViewById<Spinner>(R.id.spinner_people)
        var submit = findViewById<Button>(R.id.button_submit)

        var errorPrice = ""

        submit.setOnClickListener {
            if (montant.text.toString().equals("")){
                Toast.makeText(this, )
            }
        }

        //Spinner spinner = findViewById(R.id.spinner)
        //ArrayAdapter<Char>
    }
