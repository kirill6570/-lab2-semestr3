package task6_1

import (
	"fmt"
	"lab2-go/input"
	"strconv"
	"strings"
)

const MaxSize = 10007

type HashTable struct {
	keys       []int64
	used       []bool
	size       int
	collisions int64
}

func newTable(size int) *HashTable {
	return &HashTable{
		keys: make([]int64, size),
		used: make([]bool, size),
		size: size,
	}
}

func hash1(key int64, size int) int {
	h := int(key % int64(size))
	if h < 0 {
		h += size
	}
	return h
}

func hash2(key int64, size int) int {
	h := int(key % int64(size-1))
	if h < 0 {
		h += size - 1
	}
	return 1 + h
}

func (t *HashTable) InsertLinear(key int64) bool {
	h := hash1(key, t.size)
	for i := 0; i < t.size; i++ {
		idx := (h + i) % t.size
		if !t.used[idx] {
			t.keys[idx] = key
			t.used[idx] = true
			return true
		}
		if t.keys[idx] == key {
			return false
		}
		t.collisions++
	}
	return false
}

func (t *HashTable) InsertDouble(key int64) bool {
	h1 := hash1(key, t.size)
	h2 := hash2(key, t.size)
	for i := 0; i < t.size; i++ {
		idx := (h1 + i*h2) % t.size
		if !t.used[idx] {
			t.keys[idx] = key
			t.used[idx] = true
			return true
		}
		if t.keys[idx] == key {
			return false
		}
		t.collisions++
	}
	return false
}

func isPrime(n int) bool {
	if n < 2 {
		return false
	}
	for i := 2; i*i <= n; i++ {
		if n%i == 0 {
			return false
		}
	}
	return true
}

func Run() {
	reader := input.Reader
	fmt.Print("Размер таблицы (простое число): ")
	line, _ := reader.ReadString('\n')
	size, err := strconv.Atoi(strings.TrimSpace(line))
	if err != nil || size > MaxSize || !isPrime(size) {
		fmt.Println("Нужно простое число")
		return
	}
	fmt.Print("Количество ключей: ")
	line, _ = reader.ReadString('\n')
	count, err := strconv.Atoi(strings.TrimSpace(line))
	if err != nil || count < 0 || count > size {
		return
	}
	fmt.Printf("Введите %d ключей: ", count)
	line, _ = reader.ReadString('\n')
	parts := strings.Fields(strings.TrimSpace(line))
	t1 := newTable(size)
	t2 := newTable(size)
	for i := 0; i < count && i < len(parts); i++ {
		k, _ := strconv.ParseInt(parts[i], 10, 64)
		t1.InsertLinear(k)
		t2.InsertDouble(k)
	}
	fmt.Println("Линейное апробирование: коллизий =", t1.collisions)
	fmt.Println("Двойное хеширование:    коллизий =", t2.collisions)
}
