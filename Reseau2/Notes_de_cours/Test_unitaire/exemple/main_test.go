package main

import "testing"

type paires struct {
	param, reponse int
}

var valeursTests = []paires{
	{0, 0},
	{10, 55},
	{4, 3},
}

//Pour executer les test. Commande: go test

func TestFibR(t *testing.T) {
	for _, paire := range valeursTests {
		f := FibR(paire.param)
		if f != paire.reponse {
			t.Errorf("Attendu %d, Obtenu %d", paire.reponse, f)
		}
	}

}

func TestFibT(t *testing.T) {
	f := FibT(10)
	if f != 55 {
		t.Errorf("Attendu 55, Obtenu %d", f)
	}
}

//Pour executer les test benchamark. Commande: go test -bench=.

func BenchmarkFibR(b *testing.B) {
	for n := 0; n < b.N; n++ {
		FibR(10)
	}
}

func benchmarkFibT(valeur int, b *testing.B) {
	for n := 0; n < b.N; n++ {
		FibT(valeur)
	}
}

func BenchmarkFibT1(b *testing.B) {
	benchmarkFibT(1, b)
}

func BenchmarkFibT2(b *testing.B) {
	benchmarkFibT(2, b)
}

func BenchmarkFibT10(b *testing.B) {
	benchmarkFibT(10, b)
}
