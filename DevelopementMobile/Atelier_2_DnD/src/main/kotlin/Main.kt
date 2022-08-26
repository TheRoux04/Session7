import kotlin.random.Random

fun IntRange.random() =
    Random.nextInt((endInclusive + 1) - start) + start

var tourSpecial = 0

abstract class EtreVivant{
    abstract var attaque : Int
    abstract var defence : Int
    abstract var PV : Int
    abstract var degats : Int

    fun attaque(victime:EtreVivant):Int {
        val degats : Int
        val difficulte = victime.defence - this.attaque
        val D20 = (1..20).random()
        if (D20 >= difficulte){
            degats = victime.PV - this.degats
        }
        else{
            degats = 0
        }
        return degats
    }
}

abstract class Personnages : EtreVivant(){
    abstract fun special(victime:EtreVivant)
    fun runnnnnTahDahDahDahDahDahDahDahDahDahDahDah(perso: Personnages, ennemy: Ennemy):Boolean{
        ennemy.attaque(perso)
        return perso.PV > 0
    }
}

class Guerrier : Personnages() {
    override var attaque = 16
    override var defence = 2
    override var PV = 10
    override var degats = (1..8).random()

    override fun special(victime:EtreVivant){
        victime.PV = victime.PV - this.degats
    }
}

class Mage : Personnages() {
    override var attaque = 19
    override var defence = 8
    override var PV = 5
    override var degats = (1..4).random()

    override fun special(victime:EtreVivant){
        victime.PV = victime.PV - (4..10).random()
    }
}

class Clerc : Personnages() {
    override var attaque = 17
    override var defence = 4
    override var PV = 8
    override var degats = (1..6).random()

    override fun special(victime:EtreVivant){
        val guerison = this.PV + (2..6).random()
        if (guerison > 8){
            this.PV = 8
        }
        else{
            this.PV = guerison
        }
    }
}

class Ennemy : EtreVivant(){
    override var attaque = (15..20).random()
    override var defence = (2..8).random()
    override var PV = (3..10).random()
    override var degats = (1..5).random()
}

fun main(args: Array<String>) {
    print("Choisir votre personnage [(G)uerrier, (M)age, (C)lerc] : ")
    val input = readLine()

    if (input.equals("g")){

    }
}