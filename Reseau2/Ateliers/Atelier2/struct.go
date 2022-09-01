package main

import (
	"fmt"
	"math"
)

type Cercle struct {
	x, y, r float64
}

func (c *Cercle) aire() float64 {
	return math.Pi * c.r * c.r
}

type Rectangle struct {
	x1, y1, x2, y2 float64
}

func (r *Rectangle) aire() float64 {
	return (r.x2 - r.x1) * (r.y2 - r.y1)
}

type Forme interface {
	aire() float64
}

func aireTotale(formes ...Forme) float64 {
	var total float64
	for _, f := range formes {
		total += f.aire()
	}
	return total
}

func main() {
	c := Cercle{0, 0, 5}
	r := Rectangle{0, 0, 20, 10}
	fmt.Println(c.aire())
	fmt.Println(r.aire())
}
