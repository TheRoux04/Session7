package com.example.tp1blackjack

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.EditText
import android.widget.TextView
import androidx.fragment.app.DialogFragment
import androidx.lifecycle.ViewModelProvider

class FragmentBet : DialogFragment() {

    private lateinit var viewModel: GameViewModel

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        return inflater.inflate(R.layout.fragment_bet, container, false)
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        viewModel = ViewModelProvider(requireActivity())[GameViewModel::class.java]
        setupClickListeners(view)
        setUp(view)
    }

    override fun onStart() {
        super.onStart()
        dialog?.setCancelable(false)

    }

    fun setUp(view: View){
        viewModel.messageGame.observe(this){
            val txtMsg = view.findViewById<TextView>(R.id.txtMessageGame)
            txtMsg.text = it
        }
    }

    fun setupClickListeners(view: View) {
        val btnSubmit = view.findViewById<View>(R.id.btnSubmit)

        btnSubmit.setOnClickListener {
            val betValue = view.findViewById<EditText>(R.id.txtBet)
            if (betValue.text.toString() == "") {
                betValue.error = "Please enter a bet"
            } else if (betValue.text.toString().toInt() > viewModel.bank.value!!) {
                betValue.error = "Bet is too high"
            } else {
                if (viewModel.bank.value!! > 0) {
                    viewModel.bet.value = betValue.text.toString().toInt()
                    viewModel.bank.value = viewModel.bank.value!! - betValue.text.toString().toInt()
                    viewModel.start()
                    dismiss()
                } else {
                    viewModel.messageGame.value = "You are out of money! Please restart the game"
                }
            }
        }
    }

}