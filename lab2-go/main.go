package main

import (
	"fmt"
	"lab2-go/input"
	"strings"

	task1_stack "lab2-go/task1_stack"
	task2_set "lab2-go/task2_set"
	task3_intersection "lab2-go/task3_intersection"
	task4_pyramid "lab2-go/task4_pyramid"
	task5_tree "lab2-go/task5_tree"
	task6_1_hash "lab2-go/task6_1_hash"
	task6_2_folding "lab2-go/task6_2_folding"
	task7_lru "lab2-go/task7_lru"
)

func printMenu() {
	fmt.Println("\n===== ЛАБОРАТОРНАЯ РАБОТА №2 =====")
	fmt.Println("1. stack_parentheses (Стек и скобки)")
	fmt.Println("2. set_adt (Множество)")
	fmt.Println("3. set_intersection (Пересечение множеств)")
	fmt.Println("4. pyramid (Пирамида)")
	fmt.Println("5. tree_right_edge (Правый край дерева)")
	fmt.Println("6. hash_table (Хеш-таблица: линейное/двойное)")
	fmt.Println("7. hash_folding (Метод свёртки)")
	fmt.Println("8. lru_cache (LRU-кэш)")
	fmt.Println("0. exit")
	fmt.Print("Введите номер или имя: ")
}

func main() {
	reader := input.Reader
	for {
		printMenu()
		line, err := reader.ReadString('\n')
		if err != nil && len(line) == 0 {
			return
		}
		choice := strings.TrimSpace(line)

		if choice == "0" || choice == "exit" {
			fmt.Println("Выход.")
			return
		} else if choice == "1" || choice == "stack_parentheses" {
			task1_stack.Run()
		} else if choice == "2" || choice == "set_adt" {
			task2_set.Run()
		} else if choice == "3" || choice == "set_intersection" {
			task3_intersection.Run()
		} else if choice == "4" || choice == "pyramid" {
			task4_pyramid.Run()
		} else if choice == "5" || choice == "tree_right_edge" {
			task5_tree.Run()
		} else if choice == "6" || choice == "hash_table" {
			task6_1_hash.Run()
		} else if choice == "7" || choice == "hash_folding" {
			task6_2_folding.Run()
		} else if choice == "8" || choice == "lru_cache" {
			task7_lru.Run()
		} else {
			fmt.Println("Неверный выбор.")
		}
	}
}
