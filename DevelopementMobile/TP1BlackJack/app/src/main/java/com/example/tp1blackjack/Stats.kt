package com.example.tp1blackjack

import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity
data class Stats(
    @PrimaryKey
    @ColumnInfo(name="Rank") val rank : Int,
    @ColumnInfo(name="LeftCard",) val leftCard : Int
)
