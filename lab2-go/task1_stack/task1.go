package task1

import (
	"fmt"
	"lab2-go/input"
)

type Node struct {
	data byte
	next *Node
}

type Stack struct {
	head *Node
}

func isEmpty(s *Stack) bool { return s.head == nil }
func push(s *Stack, c byte) { s.head = &Node{data: c, next: s.head} }
func pop(s *Stack) bool {
	if isEmpty(s) {
		return false
	}
	s.head = s.head.next
	return true
}
func clear(s *Stack) {
	for pop(s) {
	}
}

func solve(src string) string {
	runes := []byte(src)
	remove := make([]bool, len(runes))
	var st Stack

	for i := 0; i < len(runes); i++ {
		if runes[i] == '(' {
			push(&st, '(')
		} else if runes[i] == ')' {
			if !isEmpty(&st) {
				pop(&st)
			} else {
				remove[i] = true
			}
		}
	}
	clear(&st)

	for i := len(runes) - 1; i >= 0; i-- {
		if runes[i] == ')' {
			push(&st, ')')
		} else if runes[i] == '(' {
			if !isEmpty(&st) {
				pop(&st)
			} else {
				remove[i] = true
			}
		}
	}
	clear(&st)

	result := make([]byte, 0, len(runes))
	for i := 0; i < len(runes); i++ {
		if !remove[i] {
			result = append(result, runes[i])
		}
	}
	return string(result)
}

func Run() {
	reader := input.Reader
	fmt.Print("Введите строку: ")
	src, _ := reader.ReadString('\n')
	if len(src) > 0 && src[len(src)-1] == '\n' {
		src = src[:len(src)-1]
	}
	fmt.Println("Результат:", solve(src))
}
