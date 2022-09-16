package com.example.atelier_pourboire

import android.annotation.SuppressLint
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.*

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        var txtPrice = findViewById<EditText>(R.id.editTextNumber_price)
        var toggleTaxes = findViewById<ToggleButton>(R.id.toggleButton_taxes)
        var spinPourcentage = findViewById<Spinner>(R.id.spinner_pourcentage)
        var spinPeople = findViewById<Spinner>(R.id.spinner_people)
        var btnSubmit = findViewById<Button>(R.id.button_submit)






        btnSubmit.setOnClickListener {
            if (txtPrice.text.toString().equals("")) {
                Toast.makeText(this, R.string.errorMontant, Toast.LENGTH_LONG).show()
            }
            else{
                var price = txtPrice.text.toString().toDouble()
                var pourcentageTip = spinPourcentage.selectedItem.toString().toDouble()
                var nbPeople = spinPeople.selectedItem.toString().toInt()

                if (toggleTaxes.isChecked){
                    var taxes = price * 0.15
                    price += taxes
                }

                price += (price * (pourcentageTip / 100))

                price /= nbPeople

                var text = "$price$"
                Toast.makeText(this, text, Toast.LENGTH_LONG).show()
            }

        }

    }


}