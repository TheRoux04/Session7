# Les Channels

## Les channels sans tampons (unbuffered channels)

Les Channels offrent une façon de communiquer entre les goroutines et de se synchroniser ensemble. Voici un exemple de synchronisation:

```go
package main
import (
  "fmt"
  "time"
)

func pinger(c chan string) {
  for i := 0; ; i++ {
    c <- "ping"
  }
}

func printer(c chan string) {
  for {
    msg := <- c
    fmt.Println(msg)
    time.Sleep(time.Second * 1)
  }
}

func main() {
  var c chan string = make(chan string)
  go pinger(c)
  go printer(c)
  var input string
  fmt.Scanln(&input)
}
```

Comme vous le constatez, la façon de créer un channel est d'utiliser la commande make et de passer le type d'information partagée par le channel.  Lors de la création d'un channel, il est possible d'établir la taille du channel en passant un second argument à make (chan type, taille). Pour une taille de 0 ou non-spécifiée comme dans l'exemple, la communication est unbuffered, synchronisée: lorsque l'émetteur (pinger) envoie un message sur le channel, il va attendre jusqu'à ce que l'afficheur (printeur) soit prêt à le recevoir. Tout comme le récepteur attend de recevoir un channel avant de continuer. Les deux opérations sont bloquantes autant pour l'émetteur que le récepteur, c'est pour cette raison qu'on appelle ce type de channels comme synchrones.

Le programme précédent va pinger sans arrêt (vous pouvez appuyez sur enter pour l'arrêter). Un channel est représenté par le mot clé chan et dans ce cas-ci on lui passe une chaîne. La flèche gauche (<-) est utilisée pour envoyée et recevoir des messages dans le channel.

c <- "ping" signifie envoyée "ping" dans le channel c.
msg := <- c signifie reçoit le message provenant de c et enregistre le dans msg.

Nous aurions pu remplacé la portion par fmt.Println(<-c) et éviter l'assignation de la variable msg.

Ajoutons cette fonction:

```go
func ponger(c chan string) {
  for i:= 0; ; i++ {
    c <- "pong"
  }
}

func main() {
  var c chan string = make(chan string)
  go pinger(c)
  go ponger(c)
  go printer(c)
  var input string
  fmt.Scanln(&input)
}
```

Le programme va maintenant y aller à tour de rôle pour afficher ping, pong.

## Méthode anonyme

Une méthode anonyme est une méthode définie par sa déclaration dans une méthode donnée. En gros, elle n'a pas de nom et ne peut être appelée par une autre méthode. Ceci permet de définir rapidement une méthode tel que dans l'exemple ci-dessous permettant de répondre à un besoin rapidement.

```go
func main() {
	func(l int, b int) {
		fmt.Println(l * b)
	}(20, 30)
}
```

Lorsque le code est rendu dans le main, il va exécuter cette méthode directement et pouvoir l'exécuter.

Ceci n'est pas vraiment très utile comme ça, mais pourrait le devenir dans un cas de channel... à suivre.

## Pipeline

Qu'est-ce qu'un pipeline? Ça sert à prendre la sortie d'une méthode et l'envoyer dans l'entrée d'une autre:

Ainsi on pourrait schématiser ceci:

`Compteur       ------>    AuCarre     ------->   Afficheur`

Comment réussir ça sous go? En utilisant deux channels:

```go
package main

import (
  "fmt"
)

func main() {
  nombres := make(chan int)
  carres := make(chan int)

  // Compteur (déclarée anonyme et inline)
  go func() {
    for x := 0; x < 100; x++ {
      nombres <- x // Envoi
    }
  }()

  // Carré (déclarée anonyme et inline)
  go func() {
    for {
      x := <-nombres  // Réception
      carres <- x * x // Envoi
    }
  }()

  // Afficheur (goroutine main)
  for {
    fmt.Println(<-carres) // Réception
  }
}
```

Il est recommandé de fermer les canaux lorsque nous savons que nous avons terminé de communiquer, n'oubliez pas que c'est synchrone, donc le close ne se produira pas tant que l'exécution ne sera pas terminée des boucles.

Il est possible de fermer les channels dès que l'émetteur n'en a plus besoin. Un simple appel à close(chan) permettra de le fermer. Ainsi, il est nécessaire de tester afin de s'assurer que le channel est toujours ouvert avant d'assigner la valeur:

```go
x, ok := <- nombres
if !ok {
  break // channel was closed and drained
}
carres <- x * x
```

Ceci est très laid et surtout horrible. Une autre fonctionnalité intéressante est l'utilisation du range plutôt que de tester à chaque fois:

```go
for x in range nombres {
    carres <- x * x
}
```

Il est possible de passer en paramètre les channels en paramètres afin d'obtenir un affichage plus consistant, veuillez noter la différence entre la déclaration d'un out channel et d'un in channel:

```go
package main

import (
  "fmt"
)

// Compteur (déclarée anonyme et inline)
func Compteur(out chan<- int) {
  for x := 0; x < 100; x++ {
    out <- x
  }
  defer close(out)
}

// Carré (déclarée anonyme et inline)
func Carre(out chan<- int, in <-chan int) {
  for x := range in {
    out <- x * x
  }
  defer close(out)
}

// Afficheur (in main goroutine)
func Afficheur(in <-chan int) {
  for x := range in {
  fmt.Println(x)
  }
}

func main() {
  nombres := make(chan int)
  carres := make(chan int)

  go Compteur(nombres)
  go Carre(carres, nombres)
  Afficheur(carres)
}
```

## Channel tampon avec taille (buffered channel)

Lors de la création d'un channel avec make, vous assignez une taille:

```go
ch = make (chan string, 3)
```
  
Une opération d'envoi sur le channel va ajouter à la fin du channel et une opération de réception va aller lire au début. Si le channel est plein, les opérations d'envoi sont bloquées tant et aussi longtemps qu'une opération de lecture n'aura pas lieu. Logiquement aussi, une opération de lecture sur un channel vide va bloquer tant qu'une information ne sera pas disponible. 

Le choix entre les deux est purement le vôtre, il est à noter que si vous avez besoin de synchronization, un unbuffered channel est mieux. Ils sont utiles lorsque vous voulez déterminer le nombre de goroutines à lancer ou limiter le travail entre deux goroutines.
package main

```go
import (
  "fmt"
  "time"
)

func main() {
  maxGoroutines := 10
  guard := make(chan struct{}, maxGoroutines)

  for i := 0; i < 30; i++ {
    guard <- struct{}{} // bloque lorsqu'on arrive à maxGoroutines
    go func(n int) {
	    worker(n)
      <-guard
    }(i)
  }
}

func worker(i int) {
  fmt.Println("travaille sur la tâche ", i)
  time.Sleep(5 * time.Second)
}
```

## Multiplexing avec select

Soit un programme effectuant ceci, démarrage d'une navette spatiale, le programme suit son cours régulier en effectuant le countdown de 10 à 1 (channel) pour effectuer le décollage, cependant à tout instant, un channel (annulation) pourrait être utilisé afin d'arrêter le countdown et d'annuler le décollage:

```go
package main

import (
	"fmt"
	"os"
	"time"
)

func main() {
  fmt.Println("Compte à rebours")
  abort := make(chan struct{})
  go func() {
    os.Stdin.Read(make([]byte, 1)) // read a single byte
    abort <- struct{}{}
  }()

  tick := time.NewTicker(1 * time.Second)

  for countdown := 10; countdown > 0; countdown-- {
    fmt.Printf("%v...", countdown)
    select {

    case <-tick.C: // Ne fait rien
    case <-abort:
      fmt.Println("Décollage annulé!")
      return // quitte la fonction main
    }
  }
  launch()
}

func launch() {
	fmt.Println("Décollage")
}
```

Il y a donc deux sources de message, un provenant du NewTicket, qui retourne un channel nommé tick.C et qui va envoyer des messages à chaque 1 secondes tel que défini dans sa création.

Il est aussi possible de recevoir un message fait par l'entremise de Enter sur le clavier.

Les deux peuvent communiquer et c'est donc pour cette raison que le select est utilisé afin d'obtenir le choix entre les deux. Un default aurait aussi pu être utilisé pour éviter des situations bloquantes:

```go
select {
    case <-abort:
      fmt.Println("Décollage annulé!")
      return // quitte la fonction main
    default:  // ne fait rien
}
```
