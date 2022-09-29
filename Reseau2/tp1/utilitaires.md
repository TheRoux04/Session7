# Utilitaires pour le TP1

## SQLITE

```go
import (
	"database/sql"
   _ "github.com/mattn/go-sqlite3"
)
```

Dans une méthode 

```go
database, err = sql.Open("sqlite3", "./chat.db")
if err != nil {
  log.Fatal(err)
}

statement, _ = database.Prepare("INSERT INTO Users (username, password, status) VALUES (?, ?, ?)")
statement.Exec("Michel", "blabla", "2") // Oui c'est bon en clair ;)

var statusDB string
err = database.QueryRow("SELECT status FROM Users WHERE ID = ?;", id).Scan(&statusDB)

if err != nil {
  log.Print(err)
}
```

Ceci ne se veut qu'une brève introduction sur le sujet, si vous désirez en apprendre plus, n'hésitez pas à consulter le github mattn

## JSON

Go supporte très bien l'intégration avec JSON:

```go
module ( 
  "encoding/json"
)
```

L'idée est de créé une structure permettant de représenter le contenu du json:

```go
// Login structure for json login
type Login struct {
  Username string `json:"username"`
  Password string `json:"password"`
}
```

Lorsque nous avons terminé la lecture de notre chaîne:

```go
var l Login
err = json.Unmarshal(contenuPage, &l)
```

ContenuPage est le contenu de la page effectuant la requête.

Si vous voulez retourner du JSON (faire une API): Avant de fmt.Print ou io.WriteString, il faut ajouter le header suivante:

```go
w.Header().Add("Content-Type", "text/json")
```