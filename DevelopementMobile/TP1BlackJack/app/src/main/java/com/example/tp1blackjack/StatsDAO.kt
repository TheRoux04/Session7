package com.example.tp1blackjack

import androidx.lifecycle.LiveData
import androidx.room.Dao
import androidx.room.Delete
import androidx.room.Insert
import androidx.room.Query

@Dao
interface StatsDAO{
    @Query("SELECT * FROM Stats")
    fun getAll(): List<Stats>

    @Insert
    fun initStat(stats: Stats)

    @Query("UPDATE Stats SET leftCard = leftCard - 1 WHERE rank = :rank")
    fun updateStats(rank: Int)

    @Query("DELETE FROM Stats")
    fun deleteStats()

}