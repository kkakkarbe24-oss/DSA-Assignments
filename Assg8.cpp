#include <iostream>
#include <climits>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
};

Node* createNode(int x) {
    Node* t = new Node;
    t->data = x;
    t->left = t->right = nullptr;
    return t;
}

Node* insertBST(Node* root, int x) {
    if (!root) return createNode(x);
    if (x < root->data) root->left = insertBST(root->left, x);
    else if (x > root->data) root->right = insertBST(root->right, x);
    return root;
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

Node* searchRec(Node* root, int key) {
    if (!root || root->data == key) return root;
    if (key < root->data) return searchRec(root->left, key);
    return searchRec(root->right, key);
}

Node* searchIter(Node* root, int key) {
    while (root) {
        if (root->data == key) return root;
        else if (key < root->data) root = root->left;
        else root = root->right;
    }
    return nullptr;
}

Node* findMax(Node* root) {
    while (root && root->right) root = root->right;
    return root;
}

Node* findMin(Node* root) {
    while (root && root->left) root = root->left;
    return root;
}

Node* inorderSuccessor(Node* root, int key) {
    Node* curr = root;
    Node* succ = nullptr;
    while (curr) {
        if (key < curr->data) { succ = curr; curr = curr->left; }
        else if (key > curr->data) curr = curr->right;
        else {
            if (curr->right) succ = findMin(curr->right);
            break;
        }
    }
    return succ;
}

Node* inorderPredecessor(Node* root, int key) {
    Node* curr = root;
    Node* pred = nullptr;
    while (curr) {
        if (key > curr->data) { pred = curr; curr = curr->right; }
        else if (key < curr->data) curr = curr->left;
        else {
            if (curr->left) pred = findMax(curr->left);
            break;
        }
    }
    return pred;
}

Node* deleteNode(Node* root, int key) {
    if (!root) return root;
    if (key < root->data) root->left = deleteNode(root->left, key);
    else if (key > root->data) root->right = deleteNode(root->right, key);
    else {
        if (!root->left && !root->right) { delete root; return nullptr; }
        else if (!root->left) { Node* t = root->right; delete root; return t; }
        else if (!root->right) { Node* t = root->left; delete root; return t; }
        else {
            Node* succ = findMin(root->right);
            root->data = succ->data;
            root->right = deleteNode(root->right, succ->data);
        }
    }
    return root;
}

int maxDepth(Node* root) {
    if (!root) return 0;
    int l = maxDepth(root->left);
    int r = maxDepth(root->right);
    return 1 + (l > r ? l : r);
}

int minDepth(Node* root) {
    if (!root) return 0;
    int l = minDepth(root->left);
    int r = minDepth(root->right);
    if (!root->left) return 1 + r;
    if (!root->right) return 1 + l;
    return 1 + (l < r ? l : r);
}

bool isBSTUtil(Node* root, long long minV, long long maxV) {
    if (!root) return true;
    if (root->data <= minV || root->data >= maxV) return false;
    return isBSTUtil(root->left, minV, root->data) &&
           isBSTUtil(root->right, root->data, maxV);
}

bool isBST(Node* root) {
    return isBSTUtil(root, LLONG_MIN, LLONG_MAX);
}

void swapInt(int &a, int &b) {
    int t = a; a = b; b = t;
}

void maxHeapify(int arr[], int n, int i) {
    int largest = i, l = 2*i + 1, r = 2*i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) { swapInt(arr[i], arr[largest]); maxHeapify(arr, n, largest); }
}

void buildMaxHeap(int arr[], int n) {
    for (int i = n/2 - 1; i >= 0; i--) maxHeapify(arr, n, i);
}

void heapSortIncreasing(int arr[], int n) {
    buildMaxHeap(arr, n);
    for (int i = n - 1; i > 0; i--) { swapInt(arr[0], arr[i]); maxHeapify(arr, i, 0); }
}

void heapSortDecreasing(int arr[], int n) {
    heapSortIncreasing(arr, n);
    for (int i = 0; i < n/2; i++) swapInt(arr[i], arr[n-1-i]);
}

class PriorityQueue {
public:
    int heap[100], size;
    PriorityQueue() { size = 0; }
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void insert(int x) {
        heap[size] = x; size++;
        int i = size - 1;
        while (i != 0 && heap[parent(i)] < heap[i]) {
            swapInt(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    int extractMax() {
        if (size == 0) return -1;
        int root = heap[0];
        heap[0] = heap[size - 1];
        size--;
        maxHeapify(heap, size, 0);
        return root;
    }

    int getMax() { return size > 0 ? heap[0] : -1; }

    void display() {
        for (int i = 0; i < size; i++) cout << heap[i] << " ";
        cout << endl;
    }
};

int main() {
    Node* root = nullptr;
    PriorityQueue pq;
    int choice, x, n, arr[100];

    while (true) {
        cout << "\n1 Insert BST\n2 Delete BST\n3 Traversals\n4 Search\n5 Max/Min\n6 Successor/Predecessor\n7 Depth\n8 Check BST\n9 Heapsort\n10 Priority Queue\n11 Exit\n";
        cin >> choice;

        if (choice == 1) { cin >> x; root = insertBST(root, x); }
        else if (choice == 2) { cin >> x; root = deleteNode(root, x); }
        else if (choice == 3) { inorder(root); cout << endl; preorder(root); cout << endl; postorder(root); cout << endl; }
        else if (choice == 4) { cin >> x; cout << (searchIter(root, x) ? 1 : 0) << endl; }
        else if (choice == 5) { cout << findMax(root)->data << " " << findMin(root)->data << endl; }
        else if (choice == 6) { cin >> x; Node* a = inorderSuccessor(root, x); Node* b = inorderPredecessor(root, x); cout << (a ? a->data : -1) << " " << (b ? b->data : -1) << endl; }
        else if (choice == 7) { cout << maxDepth(root) << " " << minDepth(root) << endl; }
        else if (choice == 8) { cout << isBST(root) << endl; }
        else if (choice == 9) {
            cin >> n;
            for (int i = 0; i < n; i++) cin >> arr[i];
            heapSortIncreasing(arr, n);
            for (int i = 0; i < n; i++) cout << arr[i] << " ";
            cout << endl;
            heapSortDecreasing(arr, n);
            for (int i = 0; i < n; i++) cout << arr[i] << " ";
            cout << endl;
        }
        else if (choice == 10) {
            int c2;
            cin >> c2;
            if (c2 == 1) { cin >> x; pq.insert(x); }
            else if (c2 == 2) cout << pq.getMax() << endl;
            else if (c2 == 3) cout << pq.extractMax() << endl;
            else if (c2 == 4) pq.display();
        }
        else break;
    }
    return 0;
}
