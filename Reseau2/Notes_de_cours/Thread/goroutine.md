# Goroutine

La majorité des gros programmes sont en réalité composés de multiples petits programmes, chacun effectuant sa tâche. C'est ainsi qu'un serveur web s'acquiert de sa tâche, chaque requête web étant un petit programme en soi.

Il serait idéal pour un programme de pouvoir exécuter ses tâches toutes en même temps (donc pour un serveur web, de pouvoir répondre à chaque requête instantannément et immédiatement). Rouler plusieurs processus en simultanées ce nomme concurrence et Go a de nombreux outils pour y parvenir en utilisant les goroutines et les channels

Une goroutine est une fonction capable d'être exécutée en parallèle à d'autres fonctions.
Pour créer une goroutine il suffit d'utiliser le mot-clé go avant l'invocation de la fonction.

```go
package main
import "fmt"

func f(n int) {
  for i := 0; i < 10; i++ {
    fmt.Println(n, ":", i)
  }
}

func main() {
  go f(0)
  var input string
  fmt.Scanln(&input)
}
```

Même si ceci n'est pas tellement apparent, ce programme exécute en réalité deux goroutines:

1. La fonction main qui est une goroutine implicite et que tous les programmes ont.
2. La seconde est créée lorsque l'appel à go f(0) est réalisé.

Normalement quand on appel une fonction externe, notre programme va exécuter toutes les lignes de la fonction appelée et après revenir à la ligne suivant l'appel. Avec une goroutine par contre, on retourne immédiatement à la ligne d'après et nous n'attendons pas l'exécution de la fonction.

C'est pour la raison qu'il y a un Scanln à la fin, afin de nous assurer que les fonctions appelées aient le temps de s'exécuter avant que le main "exit". Les goroutines sont léger et on peut facilement en créer des centaines. On peut aisément modifier notre programme pour en créer 10 très facilement:

```go
func main() {
  for i := 0; i < 10; i++ { 
    go f(i) 
  } 
  var input string 
  fmt.Scanln(&input)
}
```

Que se passe-t-il lorsque vous exécutez ce programme? Voici la sortie sur mon ordinateur:

```
1 : 0
1 : 1
1 : 2
1 : 3
1 : 4
1 : 5
1 : 6
1 : 7
1 : 8
1 : 9
5 : 0
0 : 0
0 : 1
0 : 2
0 : 3
0 : 4
0 : 5
0 : 6
0 : 7
0 : 8
0 : 9
6 : 0
6 : 1
6 : 2
6 : 3
6 : 4
6 : 5
6 : 6
6 : 7
6 : 8
6 : 9
...
```

Vous remarquez que l'exécution est plutôt synchrone, dans le sens que lorsqu'un processus a du temps d'exécution, il exécute toute sa tâche. Ajoutons du délai afin de permettre de calmer l'exécution avec time.Sleep et rand.Intn:

```go
package main
import (
  "fmt"
  "time"
  "math/rand"
)

func f(n int) {
  for i := 0; i < 10; i++ {
    fmt.Println(n, ":", i)
    amt := time.Duration(rand.Intn(250))
    time.Sleep(time.Millisecond * amt)
  }
}
```

À l'exécution, ceci crée cela:

```
1 : 0
0 : 0
2 : 0
3 : 0
6 : 0
4 : 0
5 : 0
7 : 0
8 : 0
9 : 0
7 : 1
9 : 1
3 : 1
9 : 2
4 : 1
6 : 1
1 : 1
...
```

f affiche les nombres de 0 à 9 et attend entre 0 et 250 ms après chaque exécution.
Les goroutines sont donc en mesure de s'exécuter de façon simultanée.

