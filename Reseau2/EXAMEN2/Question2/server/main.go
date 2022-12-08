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
	var PI = "3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273724587006606315588174881520920962829254091715364367892590360011330530548820466521384146951941511609433057270365759591953092186117381932611790744623799627495673518857527248912279381830119491298336733624406566430860213949463952247371907021798609437027705392171762931767523846748184676694051320005681271452635608277857713427577896091736371787214684409012249534301465495853710507922796892589235420199561121290219608640344181598136297747713099605187072113499999983729780499510597317328160963185950244594553469083026425223082533446850352619311881710100031378387528865875332083814206171776691473035982534904287554687311595628638823537875937519577818577805321712268066130019278766111959092164201989"

	listner, err := net.Listen("tcp", ":8000")
	if err != nil {
		log.Fatalln(err)
	}
	for {
		conn, err := listner.Accept()
		if err != nil {
			log.Println(err)
			continue
		}
		go gererConnection(conn, PI)
	}
}

func gererConnection(c net.Conn, PI string) {
	var returnValue string
	defer c.Close()
	for {
		//read from client
		msg, err := bufio.NewReader(c).ReadString('\n')
		if err != nil || (strings.Compare(msg, "close\n") == 0) {
			fmt.Printf("Deconnexion of client: %s\n", c.RemoteAddr().String())
			c.Close()
			return
		} else {
			//strip the newline
			msg = strings.TrimSuffix(msg, "\n")
			//find the index of the number in the PI string
			index := strings.Index(PI, msg)
			if index == -1 {
				returnValue = "Inexistant"
			} else {
				returnValue = strconv.Itoa(index)
			}
			_, err := io.WriteString(c, returnValue+"\n")
			if err != nil {
				return
			}
			time.Sleep(time.Second)
		}

	}
}
