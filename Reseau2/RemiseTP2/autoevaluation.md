# tp2-tp2-TheRoux04-1

Autoevaluation

## Fonctionnalités

**Simulateur**
Sonde : Fait et fonctionnel
Balance : Fait et fonctionnel
Reception : Fait et fonctionnel

**Agrégateur**
Sonde : Fait et fonctionnel
Balance : Fait et quelque bug mais pas toujours des fois le lenght tombe à 11 au lieu de 12 et d'autres fois le heartbeat est trop
          long alors l'agrégateur se ferme.
Reception : Fait et fonctionnel

**Moniteur**
Base : Fait mais seulement fonctionnel coté moniteur (il detect les bons flags et envoi à l'agrégateur) mais coté BD il y a des bugs
       que je ne comprend pas
Défi : Inexistant


## Spécifications

Base de donnée : Fait
README : Fait
Autoévaluation : Fait


## Qualité du code

Bons outils utilisés :  Je crois avoir utilisé les outils approprier se sera à toi d'en juger
Indentation et nommage : Je crois que mes choses sont bien nommés de façon claire et que mon indentation est belle
Séparation des fichiers : Je crois avec bien séparé de manière claire mes fichiers
Variables globales :  Aucune
Goroutines bien fermés :  Je crois ne rien avoir oublié
Pas de code de déverminage : Fait
Gestion d'erreurs : Je croit les avoirs toutes gerer et afficher 


## Sécurité

SSL Sondes : Fait
SSL Balances :  Fait
SSL Réceptions : Fait
Injection SQL : Fait


| Fonctionnalités (70): | Fonctionnel | Fonctionnel avec bug | Fait mais non fonctionnel | Incomplet ou inexistant |
| --------------------- | ----------: | -------------------: | ------------------------: | ----------------------: |
| **Simulateur**        |             |                      |                           |                         |
| Sondes                |          10 |                      |                           |                         |
| Balances              |          15 |                      |                           |                         |
| Réception             |           5 |                      |                           |                         |
| **Agrégateur**        |             |                      |                           |                         |
| Sondes                |          10 |                      |                           |                         |
| Balances              |             |                    8 |                           |                         |
| Réception             |           5 |                      |                           |                         |
| **Moniteur**          |             |                      |                           |                         |
| Base                  |             |                      |                         4 |                         |
| Défi                  |             |                      |                           |                       0 |

| Spécifications (10) | Fait | Non-fait |
| ------------------- | ---- | -------- |
| Base de données     | 3    |          |
| README.md           | 2    |          |
| Autoévaluation      | 5    |          |

| Qualité du code (30)       | Fait                           | Partiellement               | Non-fait                |
| -------------------------- | ------------------------------ | --------------------------- | ----------------------- |
| Bons outils utilisés       | Bons choix (5)                 |
| Indentation et nommage     | Parfait (3)                    |
| Séparation des fichiers    | Bonne séparation (5)           |             Puisque je ne sais vraiment pas 
| Variables globales         | Aucune (5)                     |
| Goroutines bien fermés     | Parfait (5)                    |
| Pas de code de déverminage | Parfait (2)                    |
| Gestion d'erreurs          | Toutes gérées et affichées (5) |

| Sécurité (20)  | Protégé | Non-protégé ou une faille |
| -------------- | ------- | ------------------------- |
| SSL Sondes     | 6       |                           |
| SSL Balances   | 6       |                           |
| SSL Réceptions | 6       |                           |
| Injection SQL  | 2       |                           |
