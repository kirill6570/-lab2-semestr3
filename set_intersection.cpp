#include "set_intersection.h"
#include <iostream>
#include <sstream>
#include <cstring>
using namespace std;

static int setSize(const Set& set) {
    int count = 0;
    for (int i = 0; i < SET_TABLE_SIZE; ++i) {
        SetNode* cur = set.buckets[i];
        while (cur) { ++count; cur = cur->next; }
    }
    return count;
}

static int setToArray(const Set& set, char** arr, int maxSize) {
    int idx = 0;
    for (int i = 0; i < SET_TABLE_SIZE; ++i) {
        SetNode* cur = set.buckets[i];
        while (cur && idx < maxSize) {
            arr[idx++] = cur->value;
            cur = cur->next;
        }
    }
    return idx;
}

static int countIntersection(const Set& a, const Set& b) {
    const Set* small = (setSize(a) < setSize(b)) ? &a : &b;
    const Set* big = (setSize(a) < setSize(b)) ? &b : &a;

    int capacity = setSize(*small);
    if (capacity == 0) return 0;

    char** items = new char*[capacity];
    int n = setToArray(*small, items, capacity);

    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (setContains(*big, items[i])) ++count;
    }
    delete[] items;
    return count;
}

static void printSet(const Set& set) {
    cout << "{";
    bool first = true;
    for (int i = 0; i < SET_TABLE_SIZE; ++i) {
        SetNode* cur = set.buckets[i];
        while (cur) {
            if (!first) cout << ", ";
            cout << cur->value;
            first = false;
            cur = cur->next;
        }
    }
    cout << "}";
}

void runSetIntersection() {
    int K;
    cout << "Сколько множеств? ";
    if (!(cin >> K) || K < 2) return;
    cin.ignore();

    Set* sets = new Set[K];
    for (int i = 0; i < K; ++i) {
        initSet(sets[i]);
        cout << "Множество " << (i + 1) << ": ";
        string line;
        getline(cin, line);
        stringstream ss(line);
        string token;
        while (ss >> token) setAdd(sets[i], token.c_str(), false);
    }

    int bestI = -1, bestJ = -1, bestCount = -1;
    for (int i = 0; i < K; ++i) {
        for (int j = i + 1; j < K; ++j) {
            int c = countIntersection(sets[i], sets[j]);
            if (c >= bestCount) {
                bestCount = c;
                bestI = i;
                bestJ = j;
            }
        }
    }

    cout << "\nРезультат:\n";
    cout << "Множество " << (bestI + 1) << ": ";
    printSet(sets[bestI]);
    cout << "\nМножество " << (bestJ + 1) << ": ";
    printSet(sets[bestJ]);
    cout << "\nКоличество общих элементов: " << bestCount << endl;

    for (int i = 0; i < K; ++i) clearSet(sets[i]);
    delete[] sets;
}
