#include "set_adt.h"
#include <iostream>
#include <sstream>
#include <cstring>
using namespace std;

static int hashString(const char* s) {
    int h = 0;
    for (int i = 0; s[i] != '\0'; ++i) {
        h = (h * 128 + (unsigned char)s[i]) % SET_TABLE_SIZE;
    }
    return h;
}

void initSet(Set& set) {
    for (int i = 0; i < SET_TABLE_SIZE; ++i) set.buckets[i] = nullptr;
}

void setAdd(Set& set, const char* value, bool verbose) {
    int h = hashString(value);
    SetNode* cur = set.buckets[h];
    while (cur) {
        if (strcmp(cur->value, value) == 0) {
            if (verbose) cout << "уже есть: " << value << endl;
            return;
        }
        cur = cur->next;
    }
    SetNode* node = new SetNode;
    int len = strlen(value);
    node->value = new char[len + 1];
    strcpy(node->value, value);
    node->next = set.buckets[h];
    set.buckets[h] = node;
    if (verbose) cout << "добавлено: " << value << endl;
}

void setDel(Set& set, const char* value) {
    int h = hashString(value);
    SetNode* cur = set.buckets[h];
    SetNode* prev = nullptr;
    while (cur) {
        if (strcmp(cur->value, value) == 0) {
            if (prev) prev->next = cur->next;
            else set.buckets[h] = cur->next;
            delete[] cur->value;
            delete cur;
            cout << "удалено: " << value << endl;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    cout << "не найдено: " << value << endl;
}

bool setContains(const Set& set, const char* value) {
    int h = hashString(value);
    SetNode* cur = set.buckets[h];
    while (cur) {
        if (strcmp(cur->value, value) == 0) return true;
        cur = cur->next;
    }
    return false;
}

void clearSet(Set& set) {
    for (int i = 0; i < SET_TABLE_SIZE; ++i) {
        SetNode* cur = set.buckets[i];
        while (cur) {
            SetNode* next = cur->next;
            delete[] cur->value;
            delete cur;
            cur = next;
        }
        set.buckets[i] = nullptr;
    }
}

void runSetADT() {
    Set set;
    initSet(set);

    cout << "Команды: SETADD <v>, SETDEL <v>, SET_AT <v>, EXIT" << endl;

    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string cmd, value;
        ss >> cmd >> value;

        if (cmd == "EXIT") break;
        else if (cmd == "SETADD") setAdd(set, value.c_str());
        else if (cmd == "SETDEL") setDel(set, value.c_str());
        else if (cmd == "SET_AT") {
            cout << (setContains(set, value.c_str()) ? "TRUE" : "FALSE") << endl;
        } else {
            cout << "неизвестная команда" << endl;
        }
    }

    clearSet(set);
}
