package task2

import (
	"fmt"
	"lab2-go/input"
	"strings"
)

const TableSize = 1009

type Node struct {
	value string
	next  *Node
}

type Set struct {
	buckets [TableSize]*Node
}

func hashString(s string) int {
	h := 0
	for i := 0; i < len(s); i++ {
		h = (h*128 + int(s[i])) % TableSize
	}
	return h
}

func (s *Set) Add(value string, verbose bool) {
	h := hashString(value)
	cur := s.buckets[h]
	for cur != nil {
		if cur.value == value {
			if verbose {
				fmt.Println("уже есть:", value)
			}
			return
		}
		cur = cur.next
	}
	s.buckets[h] = &Node{value: value, next: s.buckets[h]}
	if verbose {
		fmt.Println("добавлено:", value)
	}
}

func (s *Set) Del(value string) {
	h := hashString(value)
	var prev *Node
	cur := s.buckets[h]
	for cur != nil {
		if cur.value == value {
			if prev != nil {
				prev.next = cur.next
			} else {
				s.buckets[h] = cur.next
			}
			fmt.Println("удалено:", value)
			return
		}
		prev = cur
		cur = cur.next
	}
	fmt.Println("не найдено:", value)
}

func (s *Set) Contains(value string) bool {
	h := hashString(value)
	cur := s.buckets[h]
	for cur != nil {
		if cur.value == value {
			return true
		}
		cur = cur.next
	}
	return false
}

func (s *Set) Size() int {
	count := 0
	for i := 0; i < TableSize; i++ {
		cur := s.buckets[i]
		for cur != nil {
			count++
			cur = cur.next
		}
	}
	return count
}

func (s *Set) ToArray(maxSize int) []string {
	result := make([]string, 0, maxSize)
	for i := 0; i < TableSize; i++ {
		cur := s.buckets[i]
		for cur != nil && len(result) < maxSize {
			result = append(result, cur.value)
			cur = cur.next
		}
	}
	return result
}

func (s *Set) Print() {
	first := true
	for i := 0; i < TableSize; i++ {
		cur := s.buckets[i]
		for cur != nil {
			if !first {
				fmt.Print(", ")
			}
			fmt.Print(cur.value)
			first = false
			cur = cur.next
		}
	}
}

func Run() {
	var set Set
	reader := input.Reader
	fmt.Println("Команды: SETADD <v>, SETDEL <v>, SET_AT <v>, EXIT")

	for {
		fmt.Print("> ")
		line, err := reader.ReadString('\n')
		if err != nil && len(line) == 0 {
			return
		}
		line = strings.TrimSpace(line)
		if line == "" {
			continue
		}
		parts := strings.Fields(line)
		cmd := parts[0]
		value := ""
		if len(parts) > 1 {
			value = parts[1]
		}

		if cmd == "EXIT" {
			break
		} else if cmd == "SETADD" {
			set.Add(value, true)
		} else if cmd == "SETDEL" {
			set.Del(value)
		} else if cmd == "SET_AT" {
			if set.Contains(value) {
				fmt.Println("TRUE")
			} else {
				fmt.Println("FALSE")
			}
		} else {
			fmt.Println("неизвестная команда")
		}
	}
}
