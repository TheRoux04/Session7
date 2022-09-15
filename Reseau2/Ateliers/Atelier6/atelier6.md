# Numéro 1

## Solution a

Générez 10 nombres premiers aléatoires en parallèle. Vous pouvez vous inspirer de votre atelier 1 numéro 6. Chaque go/thread est responsable d'afficher sa réponse.

## Solution b

Une seule fonction sera responsable d'afficher les réponses, utilisez un channel.

# Numéro 2

## Solution a

Sans goroutine, créer un code permettant de créer une liste d'images miniatures (80x80 par exemple) pour une liste de fichier images dans un répertoire. Les fichiers ainsi réduits se nommeront nom_fichier_thumbnail.extension. Utilisez la librairie "nfnt/resize" pour vous aidez.

Mini-défi: Gardez le ratio des images.

## Solution b

Pour chaque image, faîtes une exécution en parallèle. Avec un benchmark, testez la différence entre la solution A et B.

# Numéro 3

## Solution a

Déterminer le nombre de fichier et la taille d'un répertoire en addidionnant toutes ses composantes individuelles : fichier et sous-dossiers. Vous n'aurez pas le choix de créer une fonction récursive pour la navigation des répertoires. (Considérez que les dossiers n'occupent aucune taille) Vous aurez besoin de ioutil.Readdir qui retourne les informations de fichiers et de répertoires que vous aurez besoin.

## Solution b

Comme a, mais avec des mises à jour à chaque 1 seconde afin de voir agrandir les tailles.

## Solution c - DÉFI

Faîtes-le en parallèle lorsque vous naviguez dans les répertoires.