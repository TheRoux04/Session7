# TP2

Travail individuel, remise le 12 décembre 23h55.
Lien vers le Github classroom pour la remise: https://classroom.github.com/a/6JeqiVJ1.

## Mise en situation

Vous devez faire une application réseau pour la boucherie Holiette. Cette application servira à récolter l'information des différentes sondes de l'usine, analyser les données et afficher des rapports.

Vous pouvez changer le nom de l'entreprise et les produits, tant que vous utilisez les données fournies et affichez les données demandées. Par exemple, vous pouvez peser des clowns au lieu de peser des cochons. Le tout doit respecter les règles du cégep (pas de violence ni pornographie).

Vous devez faire 3 applications: Simulateur, Agrégateur et Moniteur. Chaque application a 3 sections: Sondes, Balances et Réception.

### Simulateur

Votre simulateur doit toujours fonctionner. Si je me connecte/déconnecte 10 fois à un service le simulateur doit continuer à bien fonctionner sans fuite de mémoire.

1. Sondes: Vous avez 10 sondes qui calculent la température du four à jambon à toutes les 5 secondes (1 tick) en UDP. Chaque sonde doit être sur une goroutine. 1 seul canal UDP existe pour toutes les sondes, identifiez bien les sondes. Les sondes fonctionnent même s'il n'y a pas de connexion UDP. Chaque sonde:
   1. Prends aléatoirement entre 1 et 12 ticks de manutention (sortir le jambon précédent et préparer le nouveau);
   2. Débute à 10°C;
   3. La température augmente de 10°C à 20°C à chaque tick;
   4. La température reste stable pendant 1 tick lorsqu'elle atteins 200°C ou plus;
   5. La température redescend de 10°C à 20°C à chaque tick jusqu'à atteindre 20°C exactement;
   6. On recommence!
2. Balances: À toutes les 5 à 30 secondes (aléatoire), la balance envoie le poids d'un cochon via TCP. Ne rien faire s'il n'y a pas de connexion TCP. Le poids est envoyé sous forme de chaîne hexadécimale de 12 caractères. Les 8 premiers caractères représentent le timestamp Unix de la pesée. Les 4 autres caractères sont écrits en binaire puis convertis en hexadécimal. Les 2 premiers bits indiquent le type de cochon (00 pour refusé, 01 pour porc, 10 pour truie et 11 pour porcelet). Les 9 prochains bits indiquent le poids en kg. Les 5 derniers bits indiquent la décimale pour le poids.
   1. Exemple: 61A3 91F2 B481
   2. 8 premiers caractères hexadécimaux sont le timestamp: 28 novembre 2021 14h28
   3. Les 4 derniers caractères en binaire: 1011 0100 1000 0001
   4. Les 2 premiers bits: 10, c'est une truie
   5. Les 9 bits du milieu: 1 1010 0100, en décimal pour avoir 420 kg
   6. Les 5 derniers bits: 00001, en décimal pour avoir la décimale du poids, soit 1. Ce qui donne un poids total de 420,1 kg.
3. Réception: À l'ouverture de l'application et à toutes les minutes, il y a une nouvelle réception (si on repart l'application on recommence à une réception). Vous devez afficher les informations via une API JSON. N'affichez que les 10 dernières réceptions et n'en gardez pas plus en mémoire. Une réception contient: Le numéro de commande (incrémental), la date et heure de la réception, le nombre de cochons (aléatoirement: total, porcs, truie et porcelet).

### Agrégateur

L'agrégateur va chercher les informations des 3 modules et insère le tout dans une base de données SQLite.

1. Sondes: Insérez seulement dans la BD les 3 événements suivants, 1 seul enregistrement par jambon:
   1. Nouvelle cuisson: Moment lorsque la température passe de 20°C à plus
   2. Fin de la cuisson: Moment lorsque la température atteint plus de 200°C
   3. Fin du refroidissement: Moment lorsque la température revient à 20°C
2. Balances: Insérez les données de manières lisibles (timestamp, type et poids, pas en hexadécimal ni en binaire)
3. Réception: Insérez les nouvelles réceptions seulement, n'insérez pas de doublons. Allez vérifier les nouvelles réceptions à toutes les 30 sec, 1 min ou 2 min, à votre choix.

### Moniteur

Le moniteur permet de consulter les données en ligne de commande, utilisez les flags pour savoir quelle section afficher et la durée (dernière donnée ou X dernières minutes). Par exemple, pour afficher les balances des 5 dernières minutes:

`./moniteur -b -d 5`

Attention, le texte affiché par le moniteur doit être en français!

Défi! Ajoutez un flag qui permet de consulter la température des fours en temps réel. La température doit se mettre à jour dans la ligne de commande, vous ne devez pas ajouter de nouvelles lignes. Utilisez une librairie Go pour "dessiner" dans la ligne de commande.

## Spécifications

1. Votre code doit être sur le github donné, faites des commit/push au moins une fois par journée de travail. Aucune autre méthode de remise ne sera accepté;
2. Votre base de données doit être une SQLite, votre Git doit contenir la base de données vide ou elle doit se créer automatiquement à l'ouverture de l'aggrégateur;
3. Dans le fichier README.md de votre Git, écrivez comment exécuter chaque application (par exemple: go run simulateur.go);
4. Votre backend doit être en GO:
   1. Vous ne pouvez pas utiliser de librairie externe qui n'a pas été vu en classe sauf pour le défi;
   2. Utilisez au moins un fichier par application et par struct;
   3. Vous devez utilisez une struct avec fonction(s) pour les balances, cette struct sera partagée entre les applications Simulateur et Agrégateur;
   4. Les commentaires sont optionnels;
   5. Il n'y a pas de normes imposées, mais vous devez être constants;
   6. Utilisez les bonnes pratiques vues en classe. Par exemple:
      1. N'utilisez pas des variables globales accessibles par des goroutines;
      2. Assurez-vous de bien fermer toutes vos goroutines, ajoutez un compteur de goroutines et laissez le en commentaire;
      3. Ne pas avoir de message de déverminage dans votre console lors de la remise;
      4. Gérez toutes les erreurs, affichez des messages clairs dans les consoles;
5. Sécurité:
   1. Protégez la communication entre le Simulateur et l'Agrégateur pour les trois services avec un certificat SSL;
      1. Vos certificats doivent être dans le git, ou inscrivez dans votre README.md comment les générer et où les placer;
   2. Protégez-vous contre l'injection SQL;
6. Autoévaluation:
   1. Dans votre Git, incluez un fichier autoevaluation.md qui m'indique votre évaluation de votre projet. Si une fonctionnalité est faite en partie, décrivez ce qui est fait et/ou non-fonctionnel. Vous avez tous vos points si votre autoévaluation est verdict et réaliste.

## Correction

| Fonctionnalités (70): | Fonctionnel | Fonctionnel avec bug | Fait mais non fonctionnel | Incomplet ou inexistant |
| --------------------- | ----------: | -------------------: | ------------------------: | ----------------------: |
| **Simulateur**        |             |                      |                           |                         |
| Sondes                |          10 |                    8 |                         4 |                       0 |
| Balances              |          15 |                   12 |                         7 |                       0 |
| Réception             |           5 |                    3 |                         1 |                       0 |
| **Agrégateur**        |             |                      |                           |                         |
| Sondes                |          10 |                    8 |                         4 |                       0 |
| Balances              |          10 |                    8 |                         4 |                       0 |
| Réception             |           5 |                    3 |                         1 |                       0 |
| **Moniteur**          |             |                      |                           |                         |
| Base                  |          10 |                    8 |                         4 |                       0 |
| Défi                  |           5 |                    2 |                         0 |                       0 |

| Spécifications (10) | Fait | Non-fait |
| ------------------- | ---- | -------- |
| Base de données     | 3    | 0        |
| README.md           | 2    | 0        |
| Autoévaluation      | 5    | 0        |

| Qualité du code (30)       | Fait                           | Partiellement               | Non-fait                |
| -------------------------- | ------------------------------ | --------------------------- | ----------------------- |
| Bons outils utilisés       | Bons choix (5)                 | 1 mauvais choix (3)         | Plus de 2 erreurs (0)   |
| Indentation et nommage     | Parfait (3)                    | 1 ou 2 erreurs (3)          | Plus de 5 erreurs (0)   |
| Séparation des fichiers    | Bonne séparation (5)           | 1 ou 2 struct mal placé (2) | Plus de 2 erreurs (0)   |
| Variables globales         | Aucune (5)                     | Une (2)                     | Plus de une (0)         |
| Goroutines bien fermés     | Parfait (5)                    | N/D                         | Un oubli (0)            |
| Pas de code de déverminage | Parfait (2)                    | Un oubli (2)                | Plusieurs oublis (0)    |
| Gestion d'erreurs          | Toutes gérées et affichées (5) | Un ou deux oublis (2)       | Plus de deux oublis (0) |

| Sécurité (20)  | Protégé | Non-protégé ou une faille |
| -------------- | ------- | ------------------------- |
| SSL Sondes     | 6       | 0                         |
| SSL Balances   | 6       | 0                         |
| SSL Réceptions | 6       | 0                         |
| Injection SQL  | 2       | 0                         |

Note finale: /130