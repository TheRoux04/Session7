package com.example.examen1

import android.os.CountDownTimer
import android.util.Log
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import java.util.*

class GameViewModel() : ViewModel() {

    var sequenceSolution : MutableLiveData<List<Int>> = MutableLiveData<List<Int>>()
    var sequenceUser : MutableLiveData<List<Int>> = MutableLiveData<List<Int>>()

    var lightButton = MutableLiveData<Int>()

    var finished = MutableLiveData<Boolean>()

    var error = MutableLiveData<Boolean>()

    var message = MutableLiveData<String>()

    var levelSeq = MutableLiveData<Int>()

    var won = MutableLiveData<Boolean>()

    var click = MutableLiveData<Int>()

    init {
        sequenceSolution.value = listOf()
        sequenceUser.value = listOf()
        click.value = 0
    }

    fun addSequenceSolution(id : Int){
        sequenceSolution.value = sequenceSolution.value?.plus(id)
    }

    fun addSequenceUser(id : Int){
        sequenceUser.value = sequenceUser.value?.plus(id)
        if (sequenceUser.value!![click.value!!] != sequenceSolution.value!![click.value!!]){
            error.value = true
            message.value = "Wrong answer!!! Start New Game"
        }
        else if (sequenceUser.value!!.size == sequenceSolution.value!!.size){
            message.value = "Good answer!!!"
            won.value = true
            initiateSequence(levelSeq.value!! + 1)
        }
        click.value = click.value!! + 1
    }

    fun initiateSequence(level : Int){
        levelSeq.value = level
        finished.value = false
        sequenceSolution.value = listOf()
        val r = Random()
        var indice : Int
        for (i in 0..level){
            indice = r.nextInt(level - 1) + 1
            sequenceSolution.value = sequenceSolution.value?.toList()?.plus(indice)
        }
        playSequence()
    }

    fun playSequence(){
        var indice : Int = 0
        object:  CountDownTimer(6000,1500){
            override fun onTick(millisUntilFinished: Long) {
                lightButton.value = sequenceSolution.value!![indice]
                indice++
            }
            override fun onFinish() {
                finished.value = true
            }
        }.start()
    }
}