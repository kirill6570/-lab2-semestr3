#include <iostream>
#include <string>
using namespace std;

#include "stack_parentheses.h"
#include "set_adt.h"
#include "set_intersection.h"
#include "pyramid.h"
#include "tree_right_edge.h"
#include "hash_table.h"
#include "hash_folding.h"
#include "lru_cache.h"

void printMenu() {
    cout << "\nЛАБОРАТОРНАЯ РАБОТА №2" << endl;
    cout << "1. stack_parentheses (Стек и скобки)" << endl;
    cout << "2. set_adt (Множество)" << endl;
    cout << "3. set_intersection (Пересечение множеств)" << endl;
    cout << "4. pyramid (Пирамида)" << endl;
    cout << "5. tree_right_edge (Правый край дерева)" << endl;
    cout << "6. hash_table (Хеш-таблица: линейное/двойное)" << endl;
    cout << "7. hash_folding (Метод свёртки)" << endl;
    cout << "8. lru_cache (LRU-кэш)" << endl;
    cout << "0. exit" << endl;
    cout << "Введите номер или имя: ";
}

int main() {
    while (true) {
        printMenu();
        string choice;
        if (!(cin >> choice)) return 0;
        cin.ignore(100000, '\n');

        if (choice == "0" || choice == "exit") {
            cout << "Выход." << endl;
            return 0;
        }
        else if (choice == "1" || choice == "stack_parentheses") {
            runStackParentheses();
        }
        else if (choice == "2" || choice == "set_adt") {
            runSetADT();
        }
        else if (choice == "3" || choice == "set_intersection") {
            runSetIntersection();
        }
        else if (choice == "4" || choice == "pyramid") {
            runPyramid();
        }
        else if (choice == "5" || choice == "tree_right_edge") {
            runTreeRightEdge();
        }
        else if (choice == "6" || choice == "hash_table") {
            runHashTable();
        }
        else if (choice == "7" || choice == "hash_folding") {
            runHashFolding();
        }
        else if (choice == "8" || choice == "lru_cache") {
            runLRUCache();
        }
        else {
            cout << "Неверный выбор." << endl;
        }
    }
    return 0;
}
    