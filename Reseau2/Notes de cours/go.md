# Langage Go

[[_TOC_]]

Il n'y a pas de point-virgule à la fin de chaque ligne.

Si vous voulez tester, utilisez le paquet fmt pour afficher une donnée dans la console. Voici le fameux "*hello world*".

```go
package main

import "fmt"

func main() {
    fmt.Println("Hello World!")
}
```

Pour exécuter, rouler la ligne suivante en ligne de commande, "main.go" est le nom de votre fichier à rouler, go va exécuter la fonction "main".

```bash
go run main.go
```

Pour lire dans la console (utile pour l'atelier 1), il faut aussi utiliser le paquet fmt:

```go
var s string
fmt.Scanln(&s)
var i int
fmt.Scanf("%d", &i)
```

## Types

Go à accès aux mêmes types de bases que dans la majorité des autres langages de programmation:

- int8, int16, int32, int64, int (u en devant pour les non-signés)
- rune (alias à int32) : ceci représente une valeur unicode
- float32, float64 (nombre à virgule)
- complex64, complex128
- bool
- string

Il n'y a pas de classes, mais le langage a un type nommé struct qui vous permettra d'obtenir à peu près les mêmes fonctionnalités. Nous y reviendrons dans un chapitre ultérieur.

## Déclaration

Elle peut être statique :

```go
var x float64
x = 20.0
```

Ou dynamique lorsque le compilateur doit déterminer le type par l'entremise de la valeur qui lui est assignée, dans ce cas si, il n'y a pas de déclaration avec var de la variable. En anglais on appelle cette déclaration une "*short variable declaration*".

```go
a := 4
s := "J'aime les patates"
```

Personnellement je préfère la version longue à la version courte. Parfois vous n'aurez pas le choix d'utiliser un style ou l'autre, par exemple vous devez utiliser la version longue pour les variables globales.

Pour rendre une variable immuable, suffit d'utiliser l'identifiant const avant la déclaration de la variable:

```go
const x string = "Bonjour monde!"
x = "Réutilisation de variable"
```

Il est possible également d'effectuer de multiple assignation automatique:

```go
var i, j int = 1, 2
x, y := 3,4
```

## Array

Comme dans tous les langages de programmation, le tableau permet de stocker un ensemble d'éléments de type identique à l'intérieur.

```go
var t [3]int 
a[0] = 4
a[1] = 5
```
ou plus simplement
```go
t := [3]int{4,5}
```

Les arrays sont définis avec leur taille, donc ils sont fixes (ne peuvent donc pas être redimensionnés).

## Slice

Un slice est un sous-ensemble d'un array, par contre, il est dynamique dans le sens qu'on n'a pas besoin de spécifier sa taille lors de la création:

```go
t := [6]int{4,5,2,54,12,34}
var s []int = t[1:3]
```

C'est un range à demi ouvert, il inclut le premier, mais n'inclut pas le dernier. Donc dans ce cas-ci, on serait porté à croire 1 à 3, mais en réalité, ce n'est que 1 à 2:

```
s = [5 2]
```

Les slices ne contiennent aucune donnée, ce sont en fait que des références vers les données d'un tableau. Il s'agit presque d'un résumé.

Donc, comme vous vous en doutez, en modifiant les données d'un slice, vous allez modifier les données du tableau:

```go
noms:= [4]string{
"Michel",
"Philippe",
"Charles",
"France",
}

fmt.Println(noms)
a := noms[0:2] // Contient Michel et Philippe
b := noms[1:3] // Contient Philippe et Charles
b[0] = "XXX" // Remplace Philippe par XXX
fmt.Println(a, b)
fmt.Println(noms)
// a = Michel XXX
// b = XXX Charles
// noms = Michel XXX Charles France 
```

## Structure de contrôle

### if

Le if ne doit pas être encadré de parenthèses, par contre les différentes sections devront être encadrées d'accolades comme en C.

```go
func main() {
    if 7%2 == 0 {
        fmt.Println("7 est pair")
    } else {
        fmt.Println("7 est impair")
    }
    if 8%4 == 0 {
        fmt.Println("8 est divisible par 4")
    }
    if num := 9; num < 0 {
        fmt.Println(num, "est négatif")
    } else if num < 10 {
        fmt.Println(num, "n'a qu'un chiffre")
    } else {
        fmt.Println(num, "a plusieurs chiffres")
    }
}
```

Le else est exactement comme en C. Il peut être présent ou non. Veuillez remarquer le calcul dans la dernière possible, il est possible de faire une opération dans le if. Notez également que les paranthères ne sont pas nécessaires, mais les accolades oui!

### switch

Il est vraiment identique au C également, cependant le break n'est pas nécessaire. Il ne va qu'exécuter que le case nécessaire.

```go
func main() {
	fmt.Print("Go runs on ")
	switch os := runtime.GOOS; os {
	case "darwin":
		fmt.Println("OS X.")
	case "linux":
		fmt.Println("Linux.")
	default:
		// freebsd, openbsd,
		// plan9, windows...
		fmt.Printf("%s.\n", os)
	}
}
```

Une autre différence notable c'est qu'on peut faire un switch sur à peu près tous les types possibles:

```go
t := time.Now()
switch {
case t.Hour() < 12:
    fmt.Println("Avant-midi")
default:
    fmt.Println("Après-dîner")
}
```

## Boucles

Go n'a qu'un seul élément pour les boucles, le for.

Les 3 parties du for (comme vous vous en doutez):

- init (optionnel)
- condition (optionnel)
- post (optionnel)

Voici un exemple de déclaration:

```go
func main() {
	somme := 0
	for i := 0; i < 10; i++ {
		somme += i
	}
	fmt.Println(somme)
}
```

En go, contrairement en C/C++, il n'y a pas de parenthèses après la déclaration du for. La présence des accolades est obligatoire (bien sûr). L'itération de la boucle va se terminer aussitôt que la condition i<10 sera fausse.

Lorsque le *init* et le *post* sont retirés, vous obtenez le while (vous pouvez même retirer les ;) :

```go
func main() {
	somme := 1
	for somme < 1000 {
		somme += somme
	}
	fmt.Println(somme)
}
```

Si finalement vous retirez les 3 paramètres du for, vous obtenez alors une boucle infinie:

```go
package main

func main() {
    for {
    }
}
```

### Range

Le range permet de faire une itération sur un tableau ou un slice. Très utile pour boucler sur chacun des éléments sans être obligé d'ajouter une structure traditionnelle. Les 2 boucles suivantes font la même chose:

```go
for i := 0 ; i <= len(tab); i++ {
    // i comme indice et tab[i] comme valeur
}
for i, v := range tab {
   // i comme indice et v comme valeur
}
```

Par exemple:
```go
var pow = []int{1, 2, 4, 8, 16, 32, 64, 128}
func main() {
	for i, v := range pow {
		fmt.Printf("2**%d = %d\n", i, v)
	}
}
```

Si vous n'avez pas besoin des indices:

```go
for _, v := range pow {
    fmt.Printf("%d\n", v)
}
```

## Fonctions

Les fonctions acceptent zéro, un ou plusieurs arguments et ils peuvent retourner zéro, un ou plusieurs éléments.

Voici la syntaxe pour la fonction addition:

```go
func add(x int, y int) int {
    return x + y
}
```

Ils peuvent également retourner plusieurs arguments, remarquez la syntaxe:

```go
func swap(x, y string) (string, string) {
	return y, x
}

func main() {
	a, b := swap("hello", "world")
	fmt.Println(a, b)
}
```

### Nombre d'arguments variable

Les fonctions variables sont un type de fonctions spéciales ayant un type particulier comme dernier élément: ce dernier peut être de taille variable (remarquez les ...) dans la méthode suivante:

```go
func add(args ...int) int {
  total := 0
  for _, v := range args {
     total += v
  }
  return total
}
func main() {
  fmt.Println(add(1,2,3))
}
```

Les ... indiquent que c'est un nombre variable d'arguments, on peut y passer un slice et il va l'accepter et retourner la donnée (total).

### Fonctions en ligne

Il est possible de créer des fonctions inline, i-e définis à même une fonction:

```go
func main(){
  add := func(x, y int) int {
    return x + y
  }

  fmt.Println(add(1,2))
}
```

ou

```go
func main() {
  x := 0
  increment := func() int {
    x++
    return x
  }
  fmt.Println(increment())
  fmt.Println(increment())
}
```

### Fonction récursive

Une fonction peut s'autoappeler et ainsi créer des appels sur la pile d'exécution:

```go
func factorial(x uint) uint {
  if x == 0 {
    return 1
  }
  return x * factorial(x-1)
}
```

Go ne fait pas d'optimisation de récursion finale (*tail-recursive*). Mais utiliser cette pratique optimise un peu votre code. Voici la version récursion finale de la fonction factorial:

```go
func factTR(n uint, a uint) uint {
    if n == 1 {
        return a;
    }
    return factTR(n-1, n*a);
}

func factorial(x uint) uint {
    return factTR(x, 1)
}
```

La version "normale" prend 4.375 ns pour s'exécuter, tandis que la version avec récursion finale prend 2.646 ns pour s'exécuter, environ 60% plus rapide.

### defer

Une déclaration defer s'effectue seulement à la fin d'exécution de la fonction en cours:

```go
func main() {
  defer fmt.Println("world")
  fmt.Println("hello")
}
```

L'évaluation se fait immédiatement, mais s'exécute ultérieurement. L'exemple précédent va afficher Hello World

Les defer se font empilés de façon last in, first out. (une pile quoi!).

```go
func main() {
	fmt.Println("counting")
	for i := 0; i < 10; i++ {
		defer fmt.Println(i)
	}
	fmt.Println("done")
}
```

Ceci affiche 9 8 7 6 ... 0 (en sautant une ligne à chaque fois).
