package task3

import (
	"fmt"
	"lab2-go/input"
	"strconv"
	"strings"

	"lab2-go/task2_set"
)

func countIntersection(a, b *task2.Set) int {
	small, big := a, b
	if a.Size() > b.Size() {
		small, big = b, a
	}
	items := small.ToArray(small.Size())
	count := 0
	for _, item := range items {
		if big.Contains(item) {
			count++
		}
	}
	return count
}

func printSet(s *task2.Set) {
	fmt.Print("{")
	s.Print()
	fmt.Print("}")
}

func Run() {
	reader := input.Reader
	fmt.Print("Сколько множеств? ")
	line, _ := reader.ReadString('\n')
	K, err := strconv.Atoi(strings.TrimSpace(line))
	if err != nil || K < 2 {
		return
	}
	sets := make([]*task2.Set, K)
	for i := 0; i < K; i++ {
		sets[i] = &task2.Set{}
	}
	for i := 0; i < K; i++ {
		fmt.Printf("Множество %d: ", i+1)
		line, _ := reader.ReadString('\n')
		for _, tok := range strings.Fields(line) {
			sets[i].Add(tok, false)
		}
	}
	bestI, bestJ, bestCount := -1, -1, -1
	for i := 0; i < K; i++ {
		for j := i + 1; j < K; j++ {
			c := countIntersection(sets[i], sets[j])
			if c >= bestCount {
				bestCount = c
				bestI = i
				bestJ = j
			}
		}
	}
	fmt.Println("\nРезультат:")
	fmt.Printf("Множество %d: ", bestI+1)
	printSet(sets[bestI])
	fmt.Printf("\nМножество %d: ", bestJ+1)
	printSet(sets[bestJ])
	fmt.Printf("\nКоличество общих элементов: %d\n", bestCount)
}
