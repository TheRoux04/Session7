# TP1

Vous devez refaire un système de clavardage pour le CAI.
C'est un travail individuel.

À remettre avant le début du cours du 13 octobre.

## User stories

1. En tant que visiteur, je peux accéder au service de clavardage si un technicien est en ligne, afin d'obtenir de l'aide;
2. En tant que visiteur connecté, je peux clavarder avec le technicien afin de régler mon problème;
3. En tant que visiteur connecté, je peux mettre fin à la discussion avec le technicien afin de signaler que mon problème est résolu;
4. En tant que technicien, si le service est hors-ligne, je peux m'authentifier dans le système afin d'offrir de l'aide en ligne;
5. En tant que technicien authentifié, je peux clavarder avec chaque visiteur connecté afin de les aider;
6. En tant que technicien authentifié, je peux fermer une session d'aide afin d'enlever les visiteurs inactifs de mon interface;
7. En tant que technicien authentifié, je peux me déconnecter afin de laisser un autre technicien offrir le service (tous les clients seront déconnectés, ils devront rafraichir la page pour communiquer avec le nouveau technicien);
8. En tant qu'administrateur, je peux me connecter avec les informations admin/admin (nom d'utilisateur/mot de passe) afin d'accéder à mon interface de gestion du CAI;
9. En tant qu'administrateur, je peux effectuer le CRUD sur les techniciens afin de mettre à jour les techniciens du CAI;
10. En tant qu'administrateur, je peux consulter un rapport de connexion (heure de connexion/déconnexion du technicien, le plus récent en premier) afin de bien noter les techniciens;
11. En tant qu'administrateur, je peux me déconnecter afin de fermer ma session de manière sécuritaire;

## Spécifications

1. Votre code doit être sur le serveur gitlab du cégep. Aucune autre méthode de remise ne sera acceptée. Donnez moi accès à votre repo. Faites des commit/push au moins une fois par journée de travail;
2. Votre base de données doit être une SQLite, votre Git doit contenir la base de données et doit contenir au minimum: la structure des tables et le compte administrateur;
3. Votre frontend doit être en HTML/JavaScript/CSS.
    1. L'apparence n'est pas importante, mais l'ergonomie oui. Vous serez noté selon le temps que je me cherche dans votre application (exemple, mettre la "main" pour montrer qu'un truc est cliquable au lieu de laisser la souris normale);
    2. Affichez le maximum de messages sur l'état des services (messages d'erreur, connexion en cours au websocket, etc.);
    3. Je vais corriger sur mon mac, mon navigateur a une résolution de 1440x680;
4. Votre backend doit être en GO:
    1. Vous devez utiliser les websockets, mais pas pour tout! Demandez-vous ce qui est le plus approprité entre un websocket, une requête HTTP ou une API;
    2. Les seuls module/import venant d'internet sont "github.com/gorilla/websocket" et "github.com/mattn/go-sqlite3";
    3. Utilisez plusieurs fichiers. Par exemple, un fichier pour le serveur web, un fichier pour les structs et un fichier pour les interactions DB;
    4. Les commentaires sont optionnels;
    5. Il n'y a pas de normes imposées, mais vous devez être constants;
    6. Utilisez les bonnes pratiques vues en classe. Par exemple:
        1. N'utilisez pas des variables globales accessibles par des goroutines;
        2. Assurez vous de bien fermer toutes vos goroutines;
        3. Ne pas avoir de message d'erreur ou de déverminage dans votre console lors de la remise;
5. Sécurité:
    1. Pas besoin de communication sécurisée (https);
    2. Protégez-vous contre l'injection SQL;
    3. Les mots de passe doivent être cryptés dans la base de données;
    4. On ne devrait pas pouvoir télécharger un fichier serveur à partir d'un navigateur;
    5. Accéder à l'interface d'administration ou de technicien sans se connecter ne devrait pas être possible;
    6. Envoyer des requêtes administrateur ou technicien avec Postman (par exemple) sans être connecté ne devrait pas être possible;
    7. Votre cookie de session devrait être sécuritaire;        HTTP ONLY à TRUE

## Grille de correction

| User stories            | 60  |
| ----------------------- | --- |
| 1-4-8 - Connexion       | 10  |
| 7-11 - Déconnexion      | 5   |
| 2-5 - Clavardage        | 25  |
| 3-6 - Fin du clavardage | 5   |
| 9 - CRUD                | 10  |
| 10 - Rapport            | 5   |
| **Spécifications**      |     |
| Ergonomie               | 5   |
| Respect des normes et qualité du code | 15  |
| Sécurité                | 20  |
| Total                   | 100 |

La partie spécification ne peut pas donner plus de points que la partie User stories.