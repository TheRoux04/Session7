# Numéro 1

Ajoutez des tests automatisés à votre module mathématique (Somme, Moyenne, Écart-type, Max, Min, Médiane). Testez avec plusieurs valeurs, incluant [] et [0]

# Numéro 2

Testez la vitesse de votre processeur en calculant la moyenne d'un tableau. Testez avec des tableaux de taille: 1, 10, 100, 100.000 et 1.000.000

Pour générer un tableau contenant des entiers aléatoires, utilisez les fonctions suivantes (l'exemple génère un tableau de 5 éléments):

```go
rand.Seed(time.Now().Unix())
permutation := rand.Perm(5)
```

# Numéro 3

Reprenez votre numéro 2 de l'atelier 1 (tri bulle). Faites un benchmark pour tester la vitesse de ce tri comparé à la fonction go `sort.Ints`.