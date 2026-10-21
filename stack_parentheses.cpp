#include "stack_parentheses.h"
#include <iostream>
using namespace std;

struct StackNode {
    char data;
    StackNode* next;
};

struct Stack {
    StackNode* head = nullptr;
};

static bool isEmptyStack(const Stack& s) { return s.head == nullptr; }
static void push(Stack& s, char c) { s.head = new StackNode{c, s.head}; }
static bool pop(Stack& s) {
    if (isEmptyStack(s)) return false;
    StackNode* removed = s.head;
    s.head = removed->next;
    delete removed;
    return true;
}
static void clearStack(Stack& s) { while (pop(s)) {} }

string removeInvalidParentheses(const string& src) {
    int len = src.size();
    if (len == 0) return "";

    bool* remove = new bool[len];
    for (int i = 0; i < len; ++i) remove[i] = false;

    Stack st;

    for (int i = 0; i < len; ++i) {
        if (src[i] == '(') push(st, src[i]);
        else if (src[i] == ')') {
            if (!isEmptyStack(st)) pop(st);
            else remove[i] = true;
        }
    }
    clearStack(st);

    for (int i = len - 1; i >= 0; --i) {
        if (src[i] == ')') push(st, src[i]);
        else if (src[i] == '(') {
            if (!isEmptyStack(st)) pop(st);
            else remove[i] = true;
        }
    }
    clearStack(st);

    string result;
    for (int i = 0; i < len; ++i) {
        if (!remove[i]) result += src[i];
    }
    delete[] remove;
    return result;
}

void runStackParentheses() {
    cout << "Введите строку: ";
    string src;
    cin >> src;
    cout << "Результат: " << removeInvalidParentheses(src) << endl;
}
