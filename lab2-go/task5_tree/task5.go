package task5

import (
	"fmt"
	"lab2-go/input"
	"strconv"
	"strings"
)

type Node struct {
	data  int
	left  *Node
	right *Node
}

func insert(root *Node, value int) *Node {
	if root == nil {
		return &Node{data: value}
	}
	if value < root.data {
		root.left = insert(root.left, value)
	} else {
		root.right = insert(root.right, value)
	}
	return root
}

func printRightEdge(root *Node) {
	if root == nil {
		fmt.Println()
		return
	}
	queue := []*Node{root}
	first := true
	for len(queue) > 0 {
		levelSize := len(queue)
		var lastNode *Node
		for i := 0; i < levelSize; i++ {
			node := queue[0]
			queue = queue[1:]
			lastNode = node
			if node.left != nil {
				queue = append(queue, node.left)
			}
			if node.right != nil {
				queue = append(queue, node.right)
			}
		}
		if !first {
			fmt.Print(" ")
		}
		fmt.Print(lastNode.data)
		first = false
	}
	fmt.Println()
}

func Run() {
	reader := input.Reader
	fmt.Print("Сколько чисел? ")
	line, _ := reader.ReadString('\n')
	N, err := strconv.Atoi(strings.TrimSpace(line))
	if err != nil || N < 0 {
		return
	}
	var root *Node
	if N > 0 {
		fmt.Printf("Введите %d чисел: ", N)
		line, _ := reader.ReadString('\n')
		parts := strings.Fields(line)
		for i := 0; i < N && i < len(parts); i++ {
			v, _ := strconv.Atoi(parts[i])
			root = insert(root, v)
		}
	}
	fmt.Print("Правый край: ")
	printRightEdge(root)
}
