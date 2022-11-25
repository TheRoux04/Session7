package main

import (
	"fmt"
	"math/big"
	"math/rand"
	"time"

	r "crypto/rand"
)

/*import (
	"fmt"
	"github.com/go-playground/validator/v10"
)

type User struct {
	Email string `json:"email" validate:"required,email"`
	Name  string `json:"name" validate:"required"`
	DA    int    `json:"da" validate:"numeric,min= 1000000,max= 9999999"`
}

func main() {
	v := validator.New()
	toto := User{
		Email: "toto",
		DA:    10,
	}
	err := v.Struct(toto)
	for _, e := range err.(validator.ValidationErrors) {
		fmt.Println(e)
	}
}*/

func main() {
	rand.Seed(time.Now().Unix())
	r1 := rand.Intn(10)
	fmt.Println(r1)

	r2, _ := r.Int(r.Reader, big.NewInt(10))
	fmt.Println(r2)
}