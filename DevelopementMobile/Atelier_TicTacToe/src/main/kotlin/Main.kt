import java.lang.NumberFormatException

fun main(args: Array<String>) {
    println("Hello World!")
    val cases: MutableList<String> = mutableListOf("1", "2", "3", "4", "5", "6", "7", "8", "9")
    var tour = 0

    println("     |     |     ");
    println("  " + cases[0] + "  |  " + cases[1] + "  |  " + cases[2] + " ");
    println("_____|_____|_____");
    println("     |     |     ");
    println("  " + cases[3] + "  |  " + cases[4] + "  |  " + cases[5] + " ");
    println("_____|_____|_____");
    println("     |     |     ");
    println("  " + cases[6] + "  |  " + cases[7] + "  |  " + cases[8] + " ");
    println("     |     |     ");

    println("");

    fun coup(joueur : Int, position : Int){
        if (cases[position - 1] != "X" || cases[position - 1] != "O"){
            if (joueur % 2 == 0) cases[position - 1] = "X" else cases[position - 1] = "O"
            tour++
        }
    }

    fun verifGagner():Int{
        var result = 1
        if (cases[0] == cases[1] && cases[1] == cases[2]) result = 0
        if (cases[3] == cases[4] && cases[4] == cases[5]) result = 0
        if (cases[6] == cases[7] && cases[7] == cases[8]) result = 0
        if (cases[0] == cases[3] && cases[3] == cases[6]) result = 0
        if (cases[1] == cases[4] && cases[4] == cases[7]) result = 0
        if (cases[2] == cases[5] && cases[5] == cases[8]) result = 0
        if (cases[0] == cases[4] && cases[4] == cases[8]) result = 0
        if (cases[2] == cases[4] && cases[4] == cases[6]) result = 0

        return result

    }
    var gagner = false
    while (!gagner){
        println("Joueur " + if (tour % 2 == 0) "(X) à toi de jouer" else "(O) à toi de jouer");
        var input = readLine()

        try {
            if  ((input!!.toInt() > 0) && (input.toInt() < 10)){
                coup(tour, input.toInt())
            }
        }
        catch (ex:NumberFormatException){}

        if (tour >= 4) if (verifGagner() == 0) gagner = true


        println("     |     |     ");
        println("  " + cases[0] + "  |  " + cases[1] + "  |  " + cases[2] + " ");
        println("_____|_____|_____");
        println("     |     |     ");
        println("  " + cases[3] + "  |  " + cases[4] + "  |  " + cases[5] + " ");
        println("_____|_____|_____");
        println("     |     |     ");
        println("  " + cases[6] + "  |  " + cases[7] + "  |  " + cases[8] + " ");
        println("     |     |     ");

    }

    println("Joueur " + if ((tour - 1) % 2 == 0) "(X) à gagné" else "(O) à gagné");
}