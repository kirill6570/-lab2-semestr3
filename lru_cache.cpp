#include "lru_cache.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

const int LRU_TABLE_SIZE = 1009;

struct LRUNode {
    int key;
    int value;
    LRUNode* prev;
    LRUNode* next;
};

struct LRUHashEntry {
    int key;
    LRUNode* node;
    LRUHashEntry* next;
};

struct LRUCache {
    int capacity;
    int size;
    LRUNode* head;
    LRUNode* tail;
    LRUHashEntry* buckets[LRU_TABLE_SIZE];
};

static void initCache(LRUCache& c, int cap) {
    c.capacity = cap;
    c.size = 0;
    c.head = nullptr;
    c.tail = nullptr;
    for (int i = 0; i < LRU_TABLE_SIZE; ++i) c.buckets[i] = nullptr;
}

static int hashKey(int key) {
    int h = key % LRU_TABLE_SIZE;
    return h < 0 ? h + LRU_TABLE_SIZE : h;
}

static void addToHead(LRUCache& c, LRUNode* node) {
    node->prev = nullptr;
    node->next = c.head;
    if (c.head) c.head->prev = node;
    c.head = node;
    if (!c.tail) c.tail = node;
}

static void removeFromList(LRUCache& c, LRUNode* node) {
    if (node->prev) node->prev->next = node->next;
    else c.head = node->next;
    if (node->next) node->next->prev = node->prev;
    else c.tail = node->prev;
}

static void moveToHead(LRUCache& c, LRUNode* node) {
    removeFromList(c, node);
    addToHead(c, node);
}

static LRUNode* findNode(LRUCache& c, int key) {
    int h = hashKey(key);
    LRUHashEntry* e = c.buckets[h];
    while (e) {
        if (e->key == key) return e->node;
        e = e->next;
    }
    return nullptr;
}

static void hashInsert(LRUCache& c, int key, LRUNode* node) {
    int h = hashKey(key);
    LRUHashEntry* e = new LRUHashEntry;
    e->key = key;
    e->node = node;
    e->next = c.buckets[h];
    c.buckets[h] = e;
}

static void hashRemove(LRUCache& c, int key) {
    int h = hashKey(key);
    LRUHashEntry* cur = c.buckets[h];
    LRUHashEntry* prev = nullptr;
    while (cur) {
        if (cur->key == key) {
            if (prev) prev->next = cur->next;
            else c.buckets[h] = cur->next;
            delete cur;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

static int cacheGet(LRUCache& c, int key) {
    LRUNode* node = findNode(c, key);
    if (!node) return -1;
    moveToHead(c, node);
    return node->value;
}

static void cacheSet(LRUCache& c, int key, int value) {
    if (c.capacity == 0) return;

    LRUNode* node = findNode(c, key);
    if (node) {
        node->value = value;
        moveToHead(c, node);
        return;
    }

    LRUNode* newNode = new LRUNode;
    newNode->key = key;
    newNode->value = value;
    newNode->prev = nullptr;
    newNode->next = nullptr;

    addToHead(c, newNode);
    hashInsert(c, key, newNode);
    c.size++;

    if (c.size > c.capacity) {
        LRUNode* old = c.tail;
        hashRemove(c, old->key);
        removeFromList(c, old);
        delete old;
        c.size--;
    }
}

static void clearCache(LRUCache& c) {
    LRUNode* cur = c.head;
    while (cur) {
        LRUNode* next = cur->next;
        delete cur;
        cur = next;
    }
    for (int i = 0; i < LRU_TABLE_SIZE; ++i) {
        LRUHashEntry* e = c.buckets[i];
        while (e) {
            LRUHashEntry* next = e->next;
            delete e;
            e = next;
        }
    }
}

void runLRUCache() {
    int cap, q;
    cout << "Ёмкость кэша: ";
    if (!(cin >> cap) || cap < 0) return;

    cout << "Количество запросов: ";
    if (!(cin >> q) || q < 0) return;

    LRUCache cache;
    initCache(cache, cap);

    cin.ignore(100000, '\n');
    cout << "Введите " << q << " запросов (SET x y или GET x):\n";

    bool first = true;
    for (int i = 0; i < q; ++i) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        string cmd;
        ss >> cmd;

        if (cmd == "SET") {
            int x, y;
            if (!(ss >> x >> y)) break;
            cacheSet(cache, x, y);
        } else if (cmd == "GET") {
            int x;
            if (!(ss >> x)) break;
            int result = cacheGet(cache, x);
            if (!first) cout << " ";
            cout << result;
            first = false;
        }
    }
    cout << endl;
    clearCache(cache);
}
