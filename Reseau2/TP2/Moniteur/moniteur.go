package main

import (
	"flag"
	"fmt"
)

func main() {
	sFlag := flag.Int("s", -1, "display sondes from X last minutes")
	bFlag := flag.Int("b", -1, "display balances from X last minutes")
	rFlag := flag.Int("r", -1, "display receptions from X last minutes")
	flag.Parse()

	//if flag is  used
	if *sFlag > 0 {
		apiSondes("http://127.0.0.1:8089/api/sondes/" + fmt.Sprint(*sFlag))
	}
	if *bFlag > 0 {
		apiBalances("http://127.0.0.1:8089/api/balances/" + fmt.Sprint(*bFlag))
	}
	if *rFlag > 0 {
		apiReceptions("http://127.0.0.1:8089/api/receptions/" + fmt.Sprint(*rFlag))
	}

}
