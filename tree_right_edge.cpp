#include "tree_right_edge.h"
#include <iostream>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
};

static TreeNode* insert(TreeNode* root, int value) {
    if (!root) {
        TreeNode* node = new TreeNode;
        node->data = value;
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }
    if (value < root->data) root->left = insert(root->left, value);
    else root->right = insert(root->right, value);
    return root;
}

static void clearTree(TreeNode*& root) {
    if (!root) return;
    clearTree(root->left);
    clearTree(root->right);
    delete root;
    root = nullptr;
}

static void printRightEdge(TreeNode* root) {
    if (!root) { cout << endl; return; }

    TreeNode** queue = new TreeNode*[100000];
    int head = 0, tail = 0;
    queue[tail++] = root;
    bool first = true;

    while (head < tail) {
        int levelSize = tail - head;
        TreeNode* lastNode = nullptr;

        for (int i = 0; i < levelSize; ++i) {
            TreeNode* node = queue[head++];
            lastNode = node;
            if (node->left) queue[tail++] = node->left;
            if (node->right) queue[tail++] = node->right;
        }

        if (!first) cout << " ";
        cout << lastNode->data;
        first = false;
    }
    cout << endl;
    delete[] queue;
}

void runTreeRightEdge() {
    int N;
    cout << "Сколько чисел? ";
    if (!(cin >> N) || N < 0) return;

    TreeNode* root = nullptr;
    if (N > 0) {
        cout << "Введите " << N << " чисел: ";
        for (int i = 0; i < N; ++i) {
            int value;
            cin >> value;
            root = insert(root, value);
        }
    }

    cout << "Правый край: ";
    printRightEdge(root);
    clearTree(root);
}
