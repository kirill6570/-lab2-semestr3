package task6_2

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

const FoldMaxSize = 10007

type FoldHashTable struct {
	keys []int
	used []bool
	size int
}

func newTable(size int) *FoldHashTable {
	return &FoldHashTable{
		keys: make([]int, size),
		used: make([]bool, size),
		size: size,
	}
}

func hashFold(key int, size int) int {
	value := key
	if value < 0 {
		value = -value
	}
	s := strconv.Itoa(value)

	sum := 0
	for i := 0; i < len(s); i += 3 {
		end := i + 3
		if end > len(s) {
			end = len(s)
		}
		part, _ := strconv.Atoi(s[i:end])
		sum += part
	}
	return sum % size
}

func (t *FoldHashTable) InsertFold(key int) (int, int) {
	h := hashFold(key, t.size)
	probes := 0
	for i := 0; i < t.size; i++ {
		idx := (h + i) % t.size
		if !t.used[idx] {
			t.keys[idx] = key
			t.used[idx] = true
			return idx, probes
		}
		probes++
	}
	return -1, probes
}

func Run() {
	reader := bufio.NewReader(os.Stdin)

	fmt.Print("Размер таблицы (простое число): ")
	line, _ := reader.ReadString('\n')
	size, err := strconv.Atoi(strings.TrimSpace(line))
	if err != nil || size < 2 {
		return
	}

	fmt.Print("Количество ключей: ")
	line, _ = reader.ReadString('\n')
	count, err := strconv.Atoi(strings.TrimSpace(line))
	if err != nil || count < 1 || count > size {
		fmt.Println("Ошибка: неверное количество ключей")
		return
	}

	fmt.Printf("Введите %d ключей: ", count)
	line, _ = reader.ReadString('\n')
	parts := strings.Fields(line)
	if len(parts) < count {
		fmt.Println("Ошибка: ключей меньше, чем указано")
		return
	}

	keys := make([]int, count)
	for i := 0; i < count; i++ {
		keys[i], _ = strconv.Atoi(parts[i])
	}

	table := newTable(size)

	fmt.Println("\n Вставка ключей методом свёртки ")

	for i := 0; i < count; i++ {
		value := keys[i]
		if value < 0 {
			value = -value
		}
		s := strconv.Itoa(value)

		sum := 0
		fmt.Printf("\nКлюч %d: ", keys[i])
		first := true
		for j := 0; j < len(s); j += 3 {
			end := j + 3
			if end > len(s) {
				end = len(s)
			}
			part, _ := strconv.Atoi(s[j:end])
			sum += part
			if !first {
				fmt.Print(" + ")
			}
			fmt.Print(part)
			first = false
		}
		fmt.Printf(" = %d\n", sum)

		h := sum % size
		fmt.Printf("  начальный индекс: %d mod %d = %d\n", sum, size, h)

		finalIdx, probes := table.InsertFold(keys[i])
		if probes == 0 {
			fmt.Printf("  ячейка %d свободна → вставлен сюда\n", finalIdx)
		} else {
			fmt.Printf("  ячейка %d занята → проб: %d → вставлен в %d\n", h, probes, finalIdx)
		}

		fmt.Print("  таблица: [")
		for j := 0; j < size; j++ {
			if table.used[j] {
				fmt.Print(table.keys[j])
			} else {
				fmt.Print("_")
			}
			if j < size-1 {
				fmt.Print(" ")
			}
		}
		fmt.Println("]")
	}

	fmt.Println("\nИтоговая таблица ")
	fmt.Print("[")
	for i := 0; i < size; i++ {
		if table.used[i] {
			fmt.Print(table.keys[i])
		} else {
			fmt.Print("_")
		}
		if i < size-1 {
			fmt.Print(" ")
		}
	}
	fmt.Println("]")
	fmt.Printf("Заполнено %d из %d ячеек\n", count, size)
}