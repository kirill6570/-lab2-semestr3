#include "hash_folding.h"
#include <iostream>
#include <string>
using namespace std;

const int FOLD_MAX_SIZE = 10007;

static int hashFold(int key, int size) {
    string s = to_string(key < 0 ? -key : key);

    int sum = 0;
    for (int i = 0; i < (int)s.size(); i += 3) {
        string part = s.substr(i, 3);
        sum += stoi(part);
    }
    return sum % size;
}

struct FoldHashTable {
    int keys[FOLD_MAX_SIZE];
    bool used[FOLD_MAX_SIZE];
    int size;
};

static void initTable(FoldHashTable& t, int s) {
    t.size = s;
    for (int i = 0; i < s; ++i) {
        t.keys[i] = 0;
        t.used[i] = false;
    }
}

static int insertFold(FoldHashTable& t, int key, int& probes) {
    int h = hashFold(key, t.size);
    probes = 0;

    for (int i = 0; i < t.size; ++i) {
        int idx = (h + i) % t.size;
        if (!t.used[idx]) {
            t.keys[idx] = key;
            t.used[idx] = true;
            return idx;
        }
        ++probes;
    }
    return -1;
}

void runHashFolding() {
    int size, count;

    cout << "Размер таблицы (простое число): ";
    if (!(cin >> size) || size < 2) return;

    cout << "Количество ключей: ";
    if (!(cin >> count) || count < 1) return;

    if (count > size) {
        cout << "Ошибка: ключей больше, чем ячеек" << endl;
        return;
    }

    int* keys = new int[count];
    cout << "Введите " << count << " ключей: ";
    for (int i = 0; i < count; ++i) cin >> keys[i];

    FoldHashTable table;
    initTable(table, size);

    cout << "\nВставка ключей методом свёртки\n";

    for (int i = 0; i < count; ++i) {
        int value = keys[i] < 0 ? -keys[i] : keys[i];
        string s = to_string(value);

        int sum = 0;
        cout << "\nКлюч " << keys[i] << ": ";

        bool first = true;
        for (int j = 0; j < (int)s.size(); j += 3) {
            string part = s.substr(j, 3);
            int p = stoi(part);
            sum += p;

            if (!first) cout << " + ";
            cout << p;
            first = false;
        }
        cout << " = " << sum << endl;

        int h = sum % size;
        cout << "  начальный индекс: " << sum << " mod " << size << " = " << h << endl;

        int probes = 0;
        int finalIdx = insertFold(table, keys[i], probes);

        if (probes == 0) {
            cout << "  ячейка " << finalIdx << " свободна → вставлен сюда" << endl;
        } else {
            cout << "  ячейка " << h << " занята → проб: " << probes
                 << " → вставлен в " << finalIdx << endl;
        }

        cout << "  таблица: [";
        for (int j = 0; j < size; ++j) {
            if (table.used[j]) cout << table.keys[j];
            else cout << "_";
            if (j < size - 1) cout << " ";
        }
        cout << "]" << endl;
    }

    cout << "\nИтоговая таблица" << endl;
    cout << "[";
    for (int i = 0; i < size; ++i) {
        if (table.used[i]) cout << table.keys[i];
        else cout << "_";
        if (i < size - 1) cout << " ";
    }
    cout << "]" << endl;

    cout << "Заполнено " << count << " из " << size << " ячеек" << endl;

    delete[] keys;
}