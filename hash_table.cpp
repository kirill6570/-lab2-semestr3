#include "hash_table.h"
#include <iostream>
using namespace std;

const int HASH_MAX_SIZE = 10007;

struct HashTable {
    long long keys[HASH_MAX_SIZE];
    bool used[HASH_MAX_SIZE];
    int size;
    long long collisions;
};

static void initTable(HashTable& t, int s) {
    t.size = s;
    t.collisions = 0;
    for (int i = 0; i < s; ++i) { t.keys[i] = 0; t.used[i] = false; }
}

static int hash1(long long key, int size) {
    int h = (int)(key % size);
    return h < 0 ? h + size : h;
}

static int hash2(long long key, int size) {
    int h = (int)(key % (size - 1));
    if (h < 0) h += size - 1;
    return 1 + h;
}

static bool insertLinear(HashTable& t, long long key) {
    int h = hash1(key, t.size);
    for (int i = 0; i < t.size; ++i) {
        int idx = (h + i) % t.size;
        if (!t.used[idx]) { t.keys[idx] = key; t.used[idx] = true; return true; }
        if (t.keys[idx] == key) return false;
        ++t.collisions;
    }
    return false;
}

static bool insertDouble(HashTable& t, long long key) {
    int h1 = hash1(key, t.size);
    int h2 = hash2(key, t.size);
    for (int i = 0; i < t.size; ++i) {
        int idx = (h1 + i * h2) % t.size;
        if (!t.used[idx]) { t.keys[idx] = key; t.used[idx] = true; return true; }
        if (t.keys[idx] == key) return false;
        ++t.collisions;
    }
    return false;
}

static bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; ++i) if (n % i == 0) return false;
    return true;
}

void runHashTable() {
    int size, count;
    cout << "Размер таблицы (простое число): ";
    if (!(cin >> size) || size > HASH_MAX_SIZE || !isPrime(size)) {
        cout << "Нужно простое число\n";
        return;
    }

    cout << "Количество ключей: ";
    if (!(cin >> count) || count < 0 || count > size) return;

    long long* keys = new long long[count];
    cout << "Введите " << count << " ключей: ";
    for (int i = 0; i < count; ++i) cin >> keys[i];

    HashTable t1, t2;
    initTable(t1, size);
    initTable(t2, size);
    for (int i = 0; i < count; ++i) insertLinear(t1, keys[i]);
    for (int i = 0; i < count; ++i) insertDouble(t2, keys[i]);

    cout << "Линейное апробирование: коллизий = " << t1.collisions << endl;
    cout << "Двойное хеширование:    коллизий = " << t2.collisions << endl;

    delete[] keys;
}
