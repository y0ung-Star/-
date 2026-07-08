#include <iostream>
#include <iomanip>  // For nice table output (setw)
#include <cstdlib>  // For random numbers (rand) and memory
#include <ctime>    // To make random different on each run

using namespace std;

// =========================================================
// DATA STRUCTURES
// =========================================================

// Node of a standard Binary Search Tree (BST)
struct Node {
    int key;      // The number itself
    Node* left;   // Pointer to left child (smaller)
    Node* right;  // Pointer to right child (larger)

    // Constructor for easy node creation
    Node(int k) : key(k), left(NULL), right(NULL) {}
};

// Node of a Randomized Tree (Treap - Cartesian Tree)
struct TreapNode {
    int key;      // Search key (like in BST)
    int priority; // Random priority (like a heap)
    TreapNode* left;
    TreapNode* right;

    TreapNode(int k) : key(k), left(NULL), right(NULL) {
        priority = rand(); // Priority generated randomly upon creation!
    }
};

// =========================================================
// HELPER FUNCTIONS
// =========================================================

// Check if number is unique in array (to avoid duplicates)
bool isUnique(int* arr, int n, int val) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == val) return false;
    }
    return true;
}

// Bubble sort (written manually because std::sort is not allowed)
void bubbleSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Fill array with random UNIQUE numbers
void generateUniqueArray(int* arr, int n, int minVal, int maxVal) {
    int count = 0;
    while (count < n) {
        int val = minVal + rand() % (maxVal - minVal + 1);
        if (isUnique(arr, count, val)) {
            arr[count] = val;
            count++;
        }
    }
}

// =========================================================
// BST FUNCTIONS
// =========================================================

// Recursive insertion
void insert(Node*& root, int key) {
    if (root == NULL) {
        root = new Node(key); // Insert at empty spot
        return;
    }
    if (key < root->key)
        insert(root->left, key); // Smaller -> go left
    else if (key > root->key)
        insert(root->right, key); // Larger -> go right
}

// Search in BST
Node* search(Node* root, int key) {
    if (root == NULL || root->key == key) return root;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}

// Find minimum node (needed for deletion)
Node* findMin(Node* root) {
    while (root->left != NULL) root = root->left;
    return root;
}

// Delete node in BST
void deleteNode(Node*& root, int key) {
    if (root == NULL) return;

    if (key < root->key) {
        deleteNode(root->left, key);
    } else if (key > root->key) {
        deleteNode(root->right, key);
    } else {
        // Node found, three cases:

        // Case 1 & 2: No children or only one child
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            root = temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            root = temp;
        } else {
            // Case 3: Two children
            Node* temp = findMin(root->right);
            root->key = temp->key; // Copy successor
            deleteNode(root->right, temp->key); // Delete old successor
        }
    }
}

// Compute tree height (max depth)
int getHeight(Node* root) {
    if (root == NULL) return 0;
    int hL = getHeight(root->left);
    int hR = getHeight(root->right);
    return 1 + (hL > hR ? hL : hR);
}

// Count total nodes
int getCount(Node* root) {
    if (root == NULL) return 0;
    return 1 + getCount(root->left) + getCount(root->right);
}

// Print tree hierarchically
void printTree(Node* root, int level = 0, const char* type = "ROOT") {
    if (root == NULL) return;

    for (int i = 0; i < level; i++) cout << "    ";

    if (level == 0)
        cout << "[" << type << "] " << root->key << endl;
    else
        cout << "|__" << type << ": " << root->key << endl;

    printTree(root->left, level + 1, "L");
    printTree(root->right, level + 1, "R");
}

// In-order traversal (sorted output)
void printSorted(Node* root) {
    if (root == NULL) return;
    printSorted(root->left);
    cout << root->key << " ";
    printSorted(root->right);
}

// Delete entire tree (post-order)
void deleteTree(Node*& root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
    root = NULL;
}

// Variant task: sum of even leaf nodes
void sumEvenLeaves(Node* root, int& sum) {
    if (root == NULL) return;

    if (root->left == NULL && root->right == NULL) {
        if (root->key % 2 == 0) sum += root->key;
    }

    sumEvenLeaves(root->left, sum);
    sumEvenLeaves(root->right, sum);
}

// =========================================================
// TREAP FUNCTIONS
// =========================================================

// Split treap into l (<= key) and r (> key)
void split(TreapNode* t, int key, TreapNode*& l, TreapNode*& r) {
    if (!t)
        l = r = NULL;
    else if (key < t->key)
        split(t->left, key, l, t->left), r = t;
    else
        split(t->right, key, t->right, r), l = t;
}

// Merge two treaps
void merge(TreapNode*& t, TreapNode* l, TreapNode* r) {
    if (!l || !r)
        t = l ? l : r;
    else if (l->priority > r->priority)
        merge(l->right, l->right, r), t = l;
    else
        merge(r->left, l, r->left), t = r;
}

// Insert into treap
void insertTreap(TreapNode*& t, TreapNode* it) {
    if (!t)
        t = it;
    else if (it->priority > t->priority)
        split(t, it->key, it->left, it->right), t = it;
    else
        insertTreap(it->key < t->key ? t->left : t->right, it);
}

// Treap height
int getTreapHeight(TreapNode* t) {
    if (!t) return 0;
    int hL = getTreapHeight(t->left);
    int hR = getTreapHeight(t->right);
    return 1 + (hL > hR ? hL : hR);
}

// Delete entire treap
void deleteTreap(TreapNode*& t) {
    if (!t) return;
    deleteTreap(t->left);
    deleteTreap(t->right);
    delete t;
    t = NULL;
}

// =========================================================
// MAIN PROGRAM
// =========================================================

int main() {
    setlocale(LC_ALL, ""); // Use system locale
    srand(time(0)); // Seed random

    // --- STEP 1: Demo with small data ---
    cout << "=== STEP 1: BST Check ===" << endl;

    int n1 = 20;
    int* arr1 = new int[n1];
    generateUniqueArray(arr1, n1, 0, 100);

    Node* root = NULL;
    cout << "Keys: ";
    for (int i = 0; i < n1; i++) {
        cout << arr1[i] << " ";
        insert(root, arr1[i]);
    }
    cout << endl << endl;

    cout << "Tree structure:" << endl;
    printTree(root);
    cout << "---------------------------------" << endl;

    cout << "Height: " << getHeight(root) << endl;
    cout << "Nodes: " << getCount(root) << endl;

    cout << "Sorted (in-order): ";
    printSorted(root);
    cout << endl;

    int sum = 0;
    sumEvenLeaves(root, sum);
    cout << "Sum of even leaf nodes: " << sum << endl;

    int keyDel = arr1[0];
    cout << "\nDeleting node " << keyDel << "..." << endl;
    deleteNode(root, keyDel);

    cout << "Structure after deletion:" << endl;
    printTree(root);

    deleteTree(root);
    delete[] arr1;
    cout << endl;

    // --- STEP 2: Compare efficiency ---
    cout << "=== STEP 2: Compare heights ===" << endl;
    cout << left << setw(8) << "N" 
         << " | " << setw(15) << "Rand BST" 
         << " | " << setw(15) << "Rand Treap" 
         << " | " << setw(15) << "Sort BST" 
         << " | " << setw(15) << "Sort Treap" << endl;
    cout << string(80, '-') << endl;

    for (int n = 25; n <= 300; n += 25) {
        int* randKeys = new int[n];
        int* sortedKeys = new int[n];

        generateUniqueArray(randKeys, n, 0, 10000);

        for (int i = 0; i < n; i++) sortedKeys[i] = randKeys[i];
        bubbleSort(sortedKeys, n);

        Node* bstRand = NULL;
        TreapNode* treapRand = NULL;
        for (int i = 0; i < n; i++) {
            insert(bstRand, randKeys[i]);
            insertTreap(treapRand, new TreapNode(randKeys[i]));
        }
        int h_bst_r = getHeight(bstRand);
        int h_treap_r = getTreapHeight(treapRand);

        deleteTree(bstRand);
        deleteTreap(treapRand);

        Node* bstSort = NULL;
        TreapNode* treapSort = NULL;
        for (int i = 0; i < n; i++) {
            insert(bstSort, sortedKeys[i]);
            insertTreap(treapSort, new TreapNode(sortedKeys[i]));
        }
        int h_bst_s = getHeight(bstSort);
        int h_treap_s = getTreapHeight(treapSort);

        deleteTree(bstSort);
        deleteTreap(treapSort);

        cout << left << setw(8) << n 
             << " | " << setw(15) << h_bst_r 
             << " | " << setw(15) << h_treap_r 
             << " | " << setw(15) << h_bst_s 
             << " | " << setw(15) << h_treap_s << endl;

        delete[] randKeys;
        delete[] sortedKeys;
    }

    return 0;
}
