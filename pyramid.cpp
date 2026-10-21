#include "pyramid.h"
#include <iostream>
using namespace std;

struct Block {
    int width;
    int height;
};


struct BlockArray {
    Block* data;
    int size;
    int capacity;
};

static BlockArray* createBlockArray(int initialCapacity = 4) {
    BlockArray* arr = new BlockArray;
    arr->capacity = initialCapacity;
    arr->size = 0;
    arr->data = new Block[arr->capacity];
    return arr;
}

static void deleteBlockArray(BlockArray* arr) {
    if (!arr) return;
    delete[] arr->data;
    delete arr;
}

static void ensureCapacity(BlockArray* arr, int needed) {
    if (needed <= arr->capacity) return;
    int newCap = arr->capacity;
    while (newCap < needed) newCap *= 2;
    Block* newData = new Block[newCap];
    for (int i = 0; i < arr->size; ++i) newData[i] = arr->data[i];
    delete[] arr->data;
    arr->data = newData;
    arr->capacity = newCap;
}

static void pushBack(BlockArray* arr, const Block& b) {
    ensureCapacity(arr, arr->size + 1);
    arr->data[arr->size++] = b;
}

static bool cmpBlocks(const Block& a, const Block& b) {
    if (a.width != b.width) return a.width < b.width;
    return a.height > b.height;
}

static void sortBlockArray(BlockArray* arr) {

    for (int i = 0; i < arr->size - 1; ++i) {
        for (int j = 0; j < arr->size - i - 1; ++j) {
            if (!cmpBlocks(arr->data[j], arr->data[j + 1])) {
                Block tmp = arr->data[j];
                arr->data[j] = arr->data[j + 1];
                arr->data[j + 1] = tmp;
            }
        }
    }
}

void runPyramid() {
    int N;
    cout << "Сколько блоков? ";
    if (!(cin >> N) || N < 1) return;

    BlockArray* blocks = createBlockArray();

    cout << "Введите " << N << " пар (ширина высота):\n";
    for (int i = 0; i < N; ++i) {
        Block b;
        cin >> b.width >> b.height;
        pushBack(blocks, b);
    }

    sortBlockArray(blocks);

    long long totalHeight = 0;
    int lastWidth = -1;
    for (int i = 0; i < blocks->size; ++i) {
        if (blocks->data[i].width != lastWidth) {
            totalHeight += blocks->data[i].height;
            lastWidth = blocks->data[i].width;
        }
    }

    cout << "Максимальная высота пирамиды: " << totalHeight << endl;

    deleteBlockArray(blocks);
}