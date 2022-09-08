package main

import (
	"fmt"
	"math"
)

type Cercle struct {
	x, y, r float64
}

type Rectangle struct {
	x1, y1, x2, y2 float64
}

type Carre struct {
	x1, y1, x2, y2 float64
}

func (c *Cercle) aire() float64 {
	return math.Pi * c.r * c.r
}

func (c *Cercle) perimetre() float64 {
	return 2 * math.Pi * c.r
}

func (r *Rectangle) aire() float64 {
	return (r.x2 - r.x1) * (r.y2 - r.y1)
}

func (r *Rectangle) perimetre() float64 {
	return r.x2 + r.x2 + r.y2 + r.y2
}

func (r *Carre) aire() float64 {
	return (r.x2 - r.x1) * (r.y2 - r.y1)
}

func (r *Carre) perimetre() float64 {
	return r.x2 + r.x2 + r.y2 + r.y2
}

type Forme interface {
	aire() float64
	perimetre() float64
}

func aireTotale(formes ...Forme) float64 {
	var total float64
	for _, f := range formes {
		total += f.aire()
	}
	return total
}

func perimetreTotale(formes ...Forme) float64 {
	var total float64
	for _, f := range formes {
		total += f.perimetre()
	}
	return total
}

func toutCalculer(formes ...Forme) (float64, float64) {
	var aireTotale, perimetreTotal float64 = 0, 0
	for _, f := range formes {
		aireTotale += f.aire()
		perimetreTotal += f.perimetre()
	}
	return aireTotale, perimetreTotal
}

func main() {
	c := Cercle{0, 0, 5}
	r := Rectangle{0, 0, 20, 10}
	e := Carre{0, 0, 20, 20}
	a, p := toutCalculer(&c, &r, &e)
	fmt.Printf("Aire totale: %v\nPérimètre totale: %v\n", a, p)
}
