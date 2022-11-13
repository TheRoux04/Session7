# Synchronisation

## Attendre après des goroutines

Au lieu de faire un `fmt.Scan` à la du main ou de faire un compteur par `channel`, on peut par programmation attendre que les goroutines terminent. Vous avez besoin du import "sync". Voici les lignes de codes importantes:

```go
var wg sync.WaitGroup // Objet important, il faudra le passer en pointeur aux goroutines
wg.Add(1)             // A appeler avant de partir la goroutine, ajoute '1' au compteur du WaitGroup
wg.Done()             // A appeler à la fin de la goroutine, retire 1 au compteur du WaitGroup
wg.Wait()             // Bloque jusqu'à ce que le compteur arrive à zéro
```

## Concurrence critique
En anglais: Race condition

La concurrence critique est un problème qui arrive lorsque plusieurs goroutines accèdent et modifient une même variable, par exemple:

```go
var n int = 0
for i := 0; i < 1000; i++ {
  go func(nb *int) { nb++ }(&n)
}
```

Ce magnifique code affiche un nombre entre 960 et 975 (j'ai attendu un bon 10 secondes avec un scan pour chaque test). Pourquoi est-ce que je n'obtient pas 1000? L'instruction '++' se fait en 3 étapes: lire la valeur, l'incrémenter et l'affecter. Si 2 goroutines s'exécutent en même temps, nous aurons:

  1. g1: Lis la valeur de n : 20
  2. g1: Incrémente la valeur en mémoire : 21
  3. g2: Lis la valeur de n : 20
  4. g1: Affecte la nouvelle valeur de n : 21
  5. g2: Incrémente la valeur en mémoire : 21
  6. g2: Affecte la nouvelle valeur de n : 21

La solution que nous avons utilisés à présent est de limiter la manipulation de la variable à une seule goroutine, en utilisant un channel. Ça fonctionne mais il existe des outils plus adaptés.

## Opération atomique
De l'anglais: Atomic Operations. Dans le paquet "sync/atomic".

L'opération atomique permet de modifier une variable (nombre entier) sans problème de concurrence critique. Par exemple, dans l'exemple précédent au lieu de "n++" je vais mettre:

```go
atomic.AddUint32(nb, 1)
```

Avec cette modification ma boucle va me donner le bon chiffre.

Les opérations atomiques ne fonctionnent que sur les types: int32, int64, uint32, uint64. L'opération atomique utilise une fonction spéciale du processeur: "test-and-set". Le processeur va donc faire les 3 étapes (lecture, modification et sauvegarde) en 1 opération. Cette opération est plus lente qu'une simple affectation. J'ai roulé un benchmark sur une simple boucle qui utilise "n++" ou "atomic.AddUint64(&n, 1)". L'affectation simple a pris 8 μs (microseconde, 1000 nanosecondes) tandis que l'opération atomique a pris 266 μs, c'est 32 fois plus lent.

## Mutex
Même chose en français ou en anglais, dans le paquet "sync".

Mutex: Mutual Exclusion. Un mutex est un verrou. Une seule goroutine à la fois peut accéder au verrou. C'est comme une toilette, quand la porte est verrouillé tu attends ton tour... Exemple:

```go
var n int = 0
var m sync.Mutex
for i := 0; i < 1000; i++ {
  go func(nb *int, m *sync.Mutex) {
    m.Lock()
    nb++
    m.Unlock()
  }(&n, &m)
}
```

Le mutex utilise l'opération atomique de processeur "test-and-set" (comme les opérations atomiques Go). Pour faire simple, le Mutex crée un booléen (barré ou non) et utilise une opération atomique pour mettre ou enlever le verrou. L'opération atomique n'effectue qu'une seule opération tandis qu'avec un Mutex nous pouvons faire aussi compliqué que nous le désirons. Le Mutex est bloquant, utilisez le seulement pour le code qui en a besoin.

Côté performance, le Mutex est encore plus lent que l'opération atomique pour une addition simple. L'opération atomique prenait environ 266 μs, tandis que le mutex prend 354 μs.

Le Mutex est disponible dans tous les langages, c'est quelque chose de standard. Dans la plupart des langages, le Mutex peut seulement être libéré par le Thread qui a obtenu le verrou. Je n'ai pas testé l'inverse avec Go, mais c'est une excellente pratique à avoir!

## RWMutex

Le RWMutex est un type particulier de Mutex en Go. Il contient 2 types de verrous, un verrou "booléen" en écriture et un verrou "numérique" en écriture. Plusieurs goroutines peuvent accéder au verrou en lecture en même temps, lorsqu'on obtient un verrou en lecture Go incrémente le nombre de lecteur de manière atomique. Pour obtenir le verrou en écriture, le nombre de lecteur doit être à zéro. Lorsqu'il y a un verrou en écriture, aucune autre goroutine ne peut accéder au mutex en lecture ou écriture jusqu'à ce que l'écrivain le libère. Exemple:

```go
var m sync.RWMutex
var n int = 0
for w := 0; w < 10; w++ {
  go func(nb *int, m *sync.RWMutex) {
    m.Lock()
    *nb++
    m.Unlock()
  }(&n, &m)
  go func(nb *int, m *sync.RWMutex) {
    m.RLock()
    fmt.Println(*nb)
    m.RUnlock()
  }(&n, &m)
}
```

Le code précédent m'a affiché "2", suivit de 9 "3". 2 goroutines ont donc obtenus le mutex en écriture, suivit d'une goroutine en lecture, une autre en écriture, 9 goroutines en lectures et les 7 routines en écritures à la fin. Le comportement n'est pas stable, mais cet exemple est trop simple pour cet outil.

Dans mon benchmark, le mutex avait pris 354 μs pour faire des additions, le RWMutex a pris 719 μs. C'est deux fois plus lent! Mais si nous avons plusieurs lectures et peu d'écriture, le RWMutex sera plus rapide.

## Sémaphore
Semaphore en anglais.

Le sémaphore n'existe pas en Go, mais si vous travaillez avec un autre langage (ce qui va très probablement arriver) vous pourriez en voir. Le sémaphore permet de limiter l'accès à une ressource (pour des restrictions de performance de bd par exemple). Je le vois comme un Mutex qui compte le nombre de participants. Voir ce lien pour un exemple d'utilisation de sémaphore en C#: https://docs.microsoft.com/en-us/dotnet/api/system.threading.semaphore?view=net-5.0

N'importe quel thread peut libérer un sémaphore, pas nécessairement le thread propriétaire (n'importe quel thread peut faire + ou - 1). Un sémaphore binaire (1 seul à la fois) est très similaire à un mutex. Donc le mutex est comparable à une salle de bain (il a barré la porte, c'est le seul qui peut la débarrer) tandis que le sémaphore est comme une salle de bain publique, n'importe qui avec la clé peut ouvrir la porte même si quelqu'un utilise la ressource en ce moment...

Exemple en C++, ce code utilise 2 sémaphores binaires:

```cpp
// pingPongSemaphore.cpp

#include <iostream>
#include <semaphore>
#include <thread>

std::counting_semaphore<1> signal2Ping(0);
std::counting_semaphore<1> signal2Pong(0);

std::atomic<int> counter{};
constexpr int countlimit = 1'000'000;

void ping() {
    while(counter <= countlimit) {
        signal2Ping.acquire();
        ++counter;
        signal2Pong.release();
    }
}

void pong() {
    while(counter < countlimit) {
        signal2Pong.acquire();
        signal2Ping.release();
    }
}

int main() {

    auto start = std::chrono::system_clock::now();

    signal2Ping.release();
    std::thread t1(ping);
    std::thread t2(pong);

    t1.join();
    t2.join();

    std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
    std::cout << "Duration: " << dur.count() << " seconds" << '\n';

}
```
Source: https://modernescpp.com/index.php/semaphores-in-c-20

## Interblocage
En anglais: deadlock.

Si vous oubliez de libérer un mutex ou si vos channels attendent des réponses sans rien recevoir, vous avez un interblocage. Un interblocage survient lorsque vos threads ou goroutines attendent tous après une ressource, mais que rien ne se passe.

Un autre type de blocage est le livelock (pas de traduction). C'est ce qui arrive lorsque vos goroutines sont bloqués de manière active. Par exemple. la goroutine A obtient une erreur et demande à la goroutine B de la corriger. La goroutine B voit une erreur et demande à A de la corriger et ainsi de suite.

Les blocages peuvent provoquer une famine (ressource starvation). La famine survient lorsque la goroutine ne peut pas s'exécuter faute de ressources. Par exemple la goroutine A fait une boucle infinie et utilise 100% du CPU, la goroutine B attends son tour sur le CPU pour s'exécuter.