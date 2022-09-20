package com.example.atelier5_pourboirecontraintlayout

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.*
import java.util.*

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        var txtPrice = findViewById<EditText>(R.id.editTextNumber_price)
        var toggleTaxes = findViewById<ToggleButton>(R.id.toggleButton_taxes)
        var spinPourcentage = findViewById<Spinner>(R.id.spinner_pourcentage)
        var spinPeople = findViewById<Spinner>(R.id.spinner_people)
        var btnSubmit = findViewById<Button>(R.id.button_submit)


        binding.clickButton.setOnClickListener {
            val type = binding.beerChooserSpinner.selectedItem.toString()
                .replaceFirstChar { it.lowercase(Locale.getDefault()) }
            val intent = Intent(this, ResultActivity::class.java).apply {
                putExtra("type", type)
            }

            startActivity(intent)
        }



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

            val intent = Intent(this, ActivityResultat::class.java).apply {
                putExtra("price", price)
            }

            startActivity(intent)
        }
    }
}