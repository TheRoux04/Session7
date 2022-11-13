package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"net"
	"strconv"
	"strings"
	"time"
)

func main() {
	listner, err := net.Listen("tcp", ":8000")
	if err != nil {
		fmt.Println("Error : Count not listen on port 8000")
		log.Fatalln(err)
	} else {
		fmt.Println("Server is listening on port 8000")
	}

	for {
		conn, err2 := listner.Accept()
		if err2 != nil {
			log.Println(err2)
			fmt.Printf("Deconnexion of client: %s\n", conn.RemoteAddr().String())
			continue
		}
		fmt.Println("Connexion receive from:", conn.RemoteAddr())
		go gererConnection(conn)

		if conn.RemoteAddr() == nil {
			time.Sleep(time.Second)
			fmt.Printf("Deconnexion of client: %s\n", conn.RemoteAddr().String())
		}

		if err != nil {
			fmt.Println("Server closed")
			log.Fatalln(err)
		}
	}

}

func gererConnection(c net.Conn) {
	defer c.Close()
	var opertion string
	var tab []int
	var nb int
	for {

		msg, err := bufio.NewReader(c).ReadString('\n')
		if err != nil || (strings.Compare(msg, "close\n") == 0) {
			fmt.Printf("Deconnexion of client: %s\n", c.RemoteAddr().String())
			c.Close()
			return
		}
		msg = strings.TrimSuffix(msg, "\n")
		if msg == "=" {
			nb = 0
			switch msg {
			case "somme":
				for _, v := range tab {
					nb += v
				}
				break
			case "moyenne":
				for _, v := range tab {
					nb += v
				}
				nb = nb / len(tab)
				break
			case "min":
				nb = tab[0]
				for _, v := range tab {
					if v < nb {
						nb = v
					}
				}
				break
			case "max":
				nb = tab[0]
				for _, v := range tab {
					if v > nb {
						nb = v
					}
				}
				break
			}
			fmt.Println("Resultat: ", nb)
			_, err = io.WriteString(c, strconv.Itoa(nb)+"\n")
			if err != nil {
				fmt.Printf("Deconnexion of client: %s\n", c.RemoteAddr().String())
				c.Close()
				return
			}

		} else if opertion != "" {
			nb, _ = strconv.Atoi(msg)
			tab = append(tab, nb)
			fmt.Println("Nombre ajouter: ", nb)
		} else {
			opertion = msg
			fmt.Println("Operation: ", opertion)
		}
	}
}

// Et mettre le listener en listenTCP
/*for {
	conn, err := listner.AcceptTCP()
	conn.SetKeepAlive(true)
	conn.SetKeepAlivePeriod(time.Second)
	if err != nil {
		log.Println(err)
		continue
	}
}*/
