package com.example.tp1blackjack

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase

@Database(entities = [Stats::class], version = 1)
abstract class StatsDatabase : RoomDatabase(){
    abstract fun statsDAO() : StatsDAO

    companion object Patate {
        fun getDatabase(context: Context): StatsDatabase {
            return Room.databaseBuilder(
                context,
                StatsDatabase::class.java, "StatsDatabase"
            )
                .allowMainThreadQueries()
                .build()
        }

    }
}