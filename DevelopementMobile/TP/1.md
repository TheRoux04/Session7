# TP1

Le but du TP est de produire un jeu de blackjack.

Vous devez utiliser les ViewsModels, Retrofit et un Repository pour la gestion des parties (connexion à l'API). 

Vous devez utiliser ROOM et donc SQLite pour la gestion des statistiques.

Pour les mises avant les parties, vous devrez utiliser les fragments, afin d'afficher une interface permettant du montant à miser pour la prochaine partie.

# Règles du jeu

Le BlackJack est un jeu de carte disponible au Casino et est relativement simple dans ses rèlges. On se bat toujours contre le croupier et non contre les autres joueurs en simultanés avec nous.

Le croupier distribue 4 cartes: 

Joueur, Croupier (carte cachée), Joueur, Croupier

Les cartes valent leur valeur pour les cartes numériques, sinon le roi, la reine et le valet vaut 10. L'as vaut soit 1 ou soit 11 selon ce qui est le plus avantageux pour le joueur ou le croupier.

*Si le joueur ou le croupier a un AS et une carte valant 10 (Roi, Dame, Valet, Dix), c'est un BlackJack, c'est une victoire pour celui le possédant. Si les deux joueurs ont le BlackJack, c'est rare et une égalité :P*

Le joueur joue toujours en premier. Il a généralement les deux premiers choix, mais certaines fois le 3ième.

- Obtenir une nouvelle carte (la carte est téléchargée, affichée et la somme calculée)
- Arrêter (c'est dorénavant au tour du croupier)
- Split (dans le cas où les deux cartes sont identiques)

Le but du jeu est de se rapprocher le plus près de 21 sans jamais le dépasser. Si le joueur dépasse 21 à son tour, c'est terminé, le croupier a gagné.

Lorsque le joueur cesse d'obtenir des cartes, c'est le tour du croupier. Son règlement est simple, s'il est en bas de 16 et si le joueur le dépasse, il pige une nouvelle carte, sinon il arrête.

On compare la valeur des deux jeux et celui ayant la valeur la plus élevée gagne la partie. Si le joueur gagne, il remporte sa mise initiale sinon, il la perd.

## API

L'api répond à deux requêtes

https://c56.drynish.synology.me/getDeck 

Retourne qu'une seule information, le numéro du deck créé

https://c56.drynish.synology.me/getCard/7

Obtient une carte du deck 7

Un deck spécial (0) sera disponible afin de générer des splits. Ce sera toujours la même carte générée.

### Mises 

Le joueur commence avec 100 jetons, il peut miser entre 1 et 100 jetons pour chaque partie.

### Split

Les deux cartes doivent être identiques (pas seulement de la même valeur). La partie est séparée en deux chaque carte devient un nouveau "set". Chaque set se battant contre la main du croupier.

Supposons que vous avez deux 6:

C X 10

J 6 6

Lorsque vous choisissez split, vous devez doublez votre mise :

C X 10

J 6 Nouvelle Carte       6 Nouvelle Carte

Deux cartes sont pigées

C X 10

J 6 10   6 8 

Et vous devrez choisir à tour de rôle pour chaque regroupement de carte si vous pigez des cartes ou arrêtez.

### Statistiques

Offrir une interface afin d'offrir aux joueurs de savoir les probabilités pour la prochaine carte.r

Chaque carte pigée doit être comptabilisée selon sa valeur afin d'aider le joueur à deviner la prochaine carte.

Dans un jeu traditionnel de BlackJack, il y a 7 paquets de carte. J'ai simulé ainsi l'API. Si on ne tient compte que de leur valeur, il y a:

| Nombre | Type |
| ------ | ---- |
| 28     | As   |
| 112    | 10   |
| 28     | 9    |
| 28     | 8    |
| 28     | 7    |
| 28     | 6    |
| 28     | 5    |
| 28     | 4    |
| 28     | 3    |
| 28     | 2    |

Au premier tour, il y a donc 28/364 ou 7,69 % d'obtenir un 2.

Au fur et à mesure que les cartes sortent, le nombre de carte restante  et le nombre de carte utilisée sont ajustées.

Donc après le premier tour:

C      7 5 10

J      Valet 9

Le nombre de carte restante est le suivant:

| Nombre | Type |
| ------ | ---- |
| 28     | As   |
| 110    | 10   |
| 27     | 9    |
| 28     | 8    |
| 27     | 7    |
| 28     | 6    |
| 27     | 5    |
| 28     | 4    |
| 28     | 3    |
| 28     | 2    |

Le total est ajusté également: 359, donc 7,79% d'avoir un 2.

L'information en pourcentage pour chaque valeur sera affichée.

## Environnement

Le jeu devra rouler dans une tablette. J'ai toujours trouver que le faire sur un cell était un peu intense. Pour nous permettre d'avoir plus de place, je préfère que vous le fassiez sur une tablette. 

## Correction

| Définition                                      | Pondération |
| ----------------------------------------------- | ----------- |
| Gestion mise (Fragment + Navigation)            | /10         |
| Gestion du jeu (ViewModel)                      | /10         |
| Statistiques (Affichage) et utilisation de ROOM | /10         |
| Split                                           | /5          |
| Utilisation API (Retrofit) et Repository        | /5          |
| Qualité du code                                 | /10         |
| *Total*                                         | /50         |
