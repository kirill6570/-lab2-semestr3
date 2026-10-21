package task4

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Block struct {
	width  int
	height int
}

// ===== Свой динамический массив под Block (аналог лабы 1) =====
type BlockArray struct {
	data     []Block
	size     int
	capacity int
}

func newBlockArray(initialCapacity int) *BlockArray {
	return &BlockArray{
		data:     make([]Block, initialCapacity),
		size:     0,
		capacity: initialCapacity,
	}
}

func (a *BlockArray) ensureCapacity(needed int) {
	if needed <= a.capacity {
		return
	}
	newCap := a.capacity
	for newCap < needed {
		newCap *= 2
	}
	newData := make([]Block, newCap)
	copy(newData, a.data[:a.size])
	a.data = newData
	a.capacity = newCap
}

func (a *BlockArray) PushBack(b Block) {
	a.ensureCapacity(a.size + 1)
	a.data[a.size] = b
	a.size++
}

func (a *BlockArray) Get(i int) Block {
	return a.data[i]
}

func (a *BlockArray) Size() int {
	return a.size
}

// ===== Сортировка пузырьком =====
func (a *BlockArray) Sort() {
	for i := 0; i < a.size-1; i++ {
		for j := 0; j < a.size-i-1; j++ {
			if !cmpBlocks(a.data[j], a.data[j+1]) {
				a.data[j], a.data[j+1] = a.data[j+1], a.data[j]
			}
		}
	}
}

func cmpBlocks(a, b Block) bool {
	if a.width != b.width {
		return a.width < b.width
	}
	return a.height > b.height
}

func Run() {
	reader := bufio.NewReader(os.Stdin)

	fmt.Print("Сколько блоков? ")
	line, _ := reader.ReadString('\n')
	N, err := strconv.Atoi(strings.TrimSpace(line))
	if err != nil || N < 1 {
		return
	}

	blocks := newBlockArray(4)

	fmt.Printf("Введите %d пар (ширина высота):\n", N)
	for i := 0; i < N; i++ {
		line, _ := reader.ReadString('\n')
		parts := strings.Fields(line)
		if len(parts) < 2 {
			return
		}
		w, _ := strconv.Atoi(parts[0])
		h, _ := strconv.Atoi(parts[1])
		blocks.PushBack(Block{width: w, height: h})
	}

	blocks.Sort()

	total := 0
	lastW := -1
	for i := 0; i < blocks.Size(); i++ {
		b := blocks.Get(i)
		if b.width != lastW {
			total += b.height
			lastW = b.width
		}
	}

	fmt.Println("Максимальная высота пирамиды:", total)
}