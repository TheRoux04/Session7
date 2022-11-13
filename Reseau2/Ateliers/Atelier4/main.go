package main

func main() {

}

func somme(nbs []int) int {
	var total int
	for _, i := range nbs[1:] {
		total += nbs[i]
	}
	return total
}

func moyenne(nbs []int) int {
	laMoyenne := somme(nbs) / len(nbs)
	return laMoyenne
}

func max(nbs []int) int {
	var leMax = 0
	for _, i := range nbs[1:] {
		if i > leMax {
			leMax = i
		}
	}
	return leMax
}

func min(nbs []int) int {
	var leMin = nbs[0]
	for _, i := range nbs[1:] {
		if i < leMin {
			leMin = i
		}
	}
	return leMin
}

func mediane(nbs []int) int {
	var laMediane int
	nbs = sort(nbs)

	if len(nbs)%2 != 0 {
		laMediane = nbs[(len(nbs)-1)/2]
	} else {
		nb1 := nbs[(len(nbs)/2)-1]
		nb2 := nbs[len(nbs)/2]
		var nbsPourMoyenne = [2]int{nb1, nb2}
		laMediane = moyenne(nbsPourMoyenne)
	}
	return laMediane
}

func sort(nbs []int) []int {
	for i := 0; i < len(nbs)-1; i++ {
		for j := i + 1; j < len(nbs); j++ {
			if nbs[i] > nbs[j] {
				nbs[i], nbs[j] = nbs[j], nbs[i]
			}
		}
	}
	return nbs
}
