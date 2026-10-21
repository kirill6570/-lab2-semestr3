package task7

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

const TableSize = 1009

type Node struct {
	key   int
	value int
	prev  *Node
	next  *Node
}

type HashEntry struct {
	key  int
	node *Node
	next *HashEntry
}

type LRUCache struct {
	capacity int
	size     int
	head     *Node
	tail     *Node
	buckets  [TableSize]*HashEntry
}

func initCache(cap int) *LRUCache {
	return &LRUCache{capacity: cap}
}

func hashKey(key int) int {
	h := key % TableSize
	if h < 0 {
		h += TableSize
	}
	return h
}

func (c *LRUCache) addToHead(node *Node) {
	node.prev = nil
	node.next = c.head
	if c.head != nil {
		c.head.prev = node
	}
	c.head = node
	if c.tail == nil {
		c.tail = node
	}
}

func (c *LRUCache) removeFromList(node *Node) {
	if node.prev != nil {
		node.prev.next = node.next
	} else {
		c.head = node.next
	}
	if node.next != nil {
		node.next.prev = node.prev
	} else {
		c.tail = node.prev
	}
}

func (c *LRUCache) moveToHead(node *Node) {
	c.removeFromList(node)
	c.addToHead(node)
}

func (c *LRUCache) findNode(key int) *Node {
	h := hashKey(key)
	e := c.buckets[h]
	for e != nil {
		if e.key == key {
			return e.node
		}
		e = e.next
	}
	return nil
}

func (c *LRUCache) hashInsert(key int, node *Node) {
	h := hashKey(key)
	e := &HashEntry{key: key, node: node, next: c.buckets[h]}
	c.buckets[h] = e
}

func (c *LRUCache) hashRemove(key int) {
	h := hashKey(key)
	var prev *HashEntry
	cur := c.buckets[h]
	for cur != nil {
		if cur.key == key {
			if prev != nil {
				prev.next = cur.next
			} else {
				c.buckets[h] = cur.next
			}
			return
		}
		prev = cur
		cur = cur.next
	}
}

func (c *LRUCache) Get(key int) int {
	node := c.findNode(key)
	if node == nil {
		return -1
	}
	c.moveToHead(node)
	return node.value
}

func (c *LRUCache) Set(key, value int) {
	if c.capacity == 0 {
		return
	}
	node := c.findNode(key)
	if node != nil {
		node.value = value
		c.moveToHead(node)
		return
	}
	newNode := &Node{key: key, value: value}
	c.addToHead(newNode)
	c.hashInsert(key, newNode)
	c.size++
	if c.size > c.capacity {
		old := c.tail
		c.hashRemove(old.key)
		c.removeFromList(old)
		c.size--
	}
}

func Run() {
	reader := bufio.NewReader(os.Stdin)

	fmt.Print("Ёмкость кэша: ")
	line, _ := reader.ReadString('\n')
	cap, err := strconv.Atoi(strings.TrimSpace(line))
	if err != nil || cap < 0 {
		return
	}

	fmt.Print("Количество запросов: ")
	line, _ = reader.ReadString('\n')
	q, err := strconv.Atoi(strings.TrimSpace(line))
	if err != nil || q < 0 {
		return
	}

	cache := initCache(cap)
	fmt.Printf("Введите %d запросов (SET x y или GET x):\n", q)

	first := true
	for i := 0; i < q; i++ {
		line, _ := reader.ReadString('\n')
		line = strings.TrimSpace(line)
		parts := strings.Fields(line)
		if len(parts) == 0 {
			continue
		}
		cmd := parts[0]
		if cmd == "SET" && len(parts) >= 3 {
			x, _ := strconv.Atoi(parts[1])
			y, _ := strconv.Atoi(parts[2])
			cache.Set(x, y)
		} else if cmd == "GET" && len(parts) >= 2 {
			x, _ := strconv.Atoi(parts[1])
			result := cache.Get(x)
			if !first {
				fmt.Print(" ")
			}
			fmt.Print(result)
			first = false
		}
	}
	fmt.Println()
}