# Atelier 2 - Maps et pointeurs

## Numéro 1

Soit la chaîne suivante:

```go
var s string = "La patate douce n’est pas apparentée à la pomme de terre, malgré son nom. Elle est dotée d'une très grande richesse en pro-vitamine A (ou bêta-carotène). Elle fournit aussi une énergie de longue durée, grâce à l’amidon qu’elle renferme."
```

1. Transformez toute la chaîne en minuscule
2. Remplacez les : ' par un espace et les ( ) . , par rien "".

Écrire le code afin de créer un tableau de présence:
de = 2 en = 1 à = 2 n = 1 est = 2 grande = 1 ou = 1 douce = 1 son = 1 elle = 3 dotée = 1 richesse = 1 pas = 1 grâce = 1 amidon = 1 malgré = 1 a = 1 fournit = 1 longue = 1 terre = 1 très = 1 bêta-carotène = 1 durée = 1 l = 1 qu = 1 la = 2 d = 1 pro-vitamine = 1 aussi = 1 énergie = 1 renferme = 1 patate = 1 pomme = 1 nom = 1 une = 2 apparentée = 1

Pour vous aider, regardez les fonctions disponibles dans le package string.

## Numéro 2

Calculez le nombre d'éléments dans la suite de Syracuse pour 100 nombres aléatoires (de 1 à 200). Pour accélérer le processus, gardez le résultat de chaque calcul dans une map (pour faire une cache).

## Numéro 3

Faire une fonction qui additionne un nombre ou plus (l'utilisateur peut donner 1 seul chiffre ou des centaines en paramètre). Cette fonction n'a aucune valeur de retour, vous devez mettre le résultat dans le premier paramètre.

Cette fonction ne fait aucun sens, mais fait pratiquer quelques éléments du langage Go.

## Numéro 4

Écrire la fonction qui normalise un numéro de téléphone. La fonction reçoit le numéro de téléphone en paramètre et modifie directement ce paramètre.
Vous recevez une chaîne de 10 chiffres que vous devez transformer au format: "450 123-1234".
S'il y a plus de 10 chiffres, ajoutez le poste à la fin "450 123-1234 poste 789"

Défi: Validez que la chaîne contient au moins 10 chiffres et retirez tout ce qui n'est pas un chiffre avant de normaliser le numéro.