// queues_and_stacks.cpp
// Single file containing:
// 1) Simple queue (array) - menu driven
// 2) Circular queue (array) - menu driven
// 3) Interleave queue halves
// 4) First non-repeating character using queue (streaming)
// 5) Stack using (a) two queues and (b) one queue
//
// Compile: g++ -std=c++17 queues_and_stacks.cpp -O2 -o queues_and_stacks

#include <bits/stdc++.h>
using namespace std;

/* =========================
   1) Simple Queue (array)
   ========================= */
class SimpleQueue {
    int *A;
    int capacity;
    int frontIndex; // index of front element
    int rearIndex;  // index where next element will be inserted
    int count;
public:
    SimpleQueue(int cap=100) {
        capacity = cap;
        A = new int[capacity];
        frontIndex = 0;
        rearIndex = 0;
        count = 0;
    }
    ~SimpleQueue(){ delete[] A; }

    bool enqueue(int x) {
        if (isFull()) return false;
        A[rearIndex++] = x;
        count++;
        return true;
    }
    bool dequeue(int &out) {
        if (isEmpty()) return false;
        out = A[frontIndex++];
        count--;
        return true;
    }
    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == capacity; }
    bool peek(int &out) const {
        if (isEmpty()) return false;
        out = A[frontIndex];
        return true;
    }
    void display() const {
        if (isEmpty()) { cout << "Queue empty\n"; return; }
        cout << "Queue (front->rear): ";
        for (int i = 0; i < count; ++i) cout << A[frontIndex + i] << (i+1==count?'\n':' ');
    }
    void reset() {
        frontIndex = rearIndex = count = 0;
    }
};

/* =========================
   2) Circular Queue (array)
   ========================= */
class CircularQueue {
    int *A;
    int capacity;
    int frontIndex; // index of front element
    int rearIndex;  // index of last element
    int count;
public:
    CircularQueue(int cap=100) {
        capacity = cap;
        A = new int[capacity];
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }
    ~CircularQueue(){ delete[] A; }

    bool enqueue(int x) {
        if (isFull()) return false;
        rearIndex = (rearIndex + 1) % capacity;
        A[rearIndex] = x;
        count++;
        return true;
    }
    bool dequeue(int &out) {
        if (isEmpty()) return false;
        out = A[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        count--;
        return true;
    }
    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == capacity; }
    bool peek(int &out) const {
        if (isEmpty()) return false;
        out = A[frontIndex];
        return true;
    }
    void display() const {
        if (isEmpty()) { cout << "Circular queue empty\n"; return; }
        cout << "Circular Queue (front->rear): ";
        for (int i = 0, idx = frontIndex; i < count; ++i, idx = (idx+1)%capacity)
            cout << A[idx] << (i+1==count?'\n':' ');
    }
    void reset() {
        frontIndex = 0; rearIndex = -1; count = 0;
    }
};

/* =========================
   3) Interleave queue halves
   Example: 4 7 11 20 5 9 -> 4 20 7 5 11 9
   Works for even-sized queue. If odd, last element stays at end.
   Implementation uses std::queue<int>.
   ========================= */
void interleaveQueue(queue<int> &q) {
    int n = (int)q.size();
    if (n <= 2) return;
    int half = n / 2;
    queue<int> first, second;

    for (int i = 0; i < half; ++i) { first.push(q.front()); q.pop(); }
    while (!q.empty()) { second.push(q.front()); q.pop(); }

    queue<int> res;
    while (!first.empty() || !second.empty()) {
        if (!first.empty()) { res.push(first.front()); first.pop(); }
        if (!second.empty()) { res.push(second.front()); second.pop(); }
    }
    q = move(res);
}

/* =========================
   4) First non-repeating character using queue (stream of chars)
   For each incoming char we output the current first non-repeating char or -1
   Example input: a a b c (space separated) -> outputs: a -1 b b
   Implementation: freq map + queue<char>
   ========================= */
vector<string> firstNonRepeatingChars(const vector<char>& inputs) {
    vector<string> result;
    unordered_map<char,int> freq;
    queue<char> q;
    for (char ch : inputs) {
        freq[ch]++;
        q.push(ch);
        while (!q.empty() && freq[q.front()] > 1) q.pop();
        if (q.empty()) result.push_back("-1");
        else {
            string s; s.push_back(q.front());
            result.push_back(s);
        }
    }
    return result;
}

/* =========================
   5a) Stack using two queues (push costly)
   push(x):
     enqueue x into q2
     move all items from q1 to q2
     swap(q1,q2)
   pop():
     dequeue from q1
   ========================= */
class StackTwoQueues {
    queue<int> q1, q2;
public:
    void push(int x) {
        q2.push(x);
        while (!q1.empty()) { q2.push(q1.front()); q1.pop(); }
        swap(q1, q2);
    }
    bool pop(int &out) {
        if (q1.empty()) return false;
        out = q1.front(); q1.pop(); return true;
    }
    bool peek(int &out) {
        if (q1.empty()) return false;
        out = q1.front(); return true;
    }
    bool isEmpty() const { return q1.empty(); }
    void display() const {
        queue<int> tmp = q1;
        cout << "Stack (top -> bottom): ";
        // q1 front is top
        while (!tmp.empty()) {
            cout << tmp.front();
            tmp.pop();
            if (!tmp.empty()) cout << " ";
        }
        cout << "\n";
    }
};

/* =========================
   5b) Stack using one queue
   push(x): enqueue x, then rotate (size-1) elements from front to back
   pop(): dequeue
   ========================= */
class StackOneQueue {
    queue<int> q;
public:
    void push(int x) {
        q.push(x);
        int sz = (int)q.size();
        for (int i = 0; i < sz-1; ++i) {
            q.push(q.front());
            q.pop();
        }
    }
    bool pop(int &out) {
        if (q.empty()) return false;
        out = q.front(); q.pop(); return true;
    }
    bool peek(int &out) {
        if (q.empty()) return false;
        out = q.front(); return true;
    }
    bool isEmpty() const { return q.empty(); }
    void display() const {
        queue<int> tmp = q;
        cout << "Stack (top -> bottom): ";
        while (!tmp.empty()) {
            cout << tmp.front();
            tmp.pop();
            if (!tmp.empty()) cout << " ";
        }
        cout << "\n";
    }
};

/* =========================
   Menus & Helpers
   ========================= */
void simpleQueueMenu() {
    int cap;
    cout << "Enter capacity for simple queue (default 10): ";
    if (!(cin >> cap)) cap = 10;
    SimpleQueue q(cap);
    while (true) {
        cout << "\n--- Simple Queue Menu ---\n"
             << "1. enqueue\n2. dequeue\n3. isEmpty\n4. isFull\n5. peek\n6. display\n0. return\nChoose: ";
        int opt; if (!(cin >> opt)) { cin.clear(); cin.ignore(1<<20,'\n'); continue; }
        if (opt == 0) break;
        if (opt == 1) {
            int x; cout << "Enter value: "; cin >> x;
            if (!q.enqueue(x)) cout << "Queue is full.\n";
            else cout << "Enqueued " << x << '\n';
        } else if (opt == 2) {
            int out;
            if (!q.dequeue(out)) cout << "Queue is empty.\n";
            else cout << "Dequeued: " << out << '\n';
        } else if (opt == 3) cout << (q.isEmpty()? "Empty\n":"Not empty\n");
        else if (opt == 4) cout << (q.isFull()? "Full\n":"Not full\n");
        else if (opt == 5) {
            int out; if (!q.peek(out)) cout << "Queue is empty.\n"; else cout << "Front: " << out << '\n';
        } else if (opt == 6) q.display();
        else cout << "Invalid\n";
    }
}

void circularQueueMenu() {
    int cap;
    cout << "Enter capacity for circular queue (default 10): ";
    if (!(cin >> cap)) cap = 10;
    CircularQueue q(cap);
    while (true) {
        cout << "\n--- Circular Queue Menu ---\n"
             << "1. enqueue\n2. dequeue\n3. isEmpty\n4. isFull\n5. peek\n6. display\n0. return\nChoose: ";
        int opt; if (!(cin >> opt)) { cin.clear(); cin.ignore(1<<20,'\n'); continue; }
        if (opt == 0) break;
        if (opt == 1) {
            int x; cout << "Enter value: "; cin >> x;
            if (!q.enqueue(x)) cout << "Circular Queue is full.\n";
            else cout << "Enqueued " << x << '\n';
        } else if (opt == 2) {
            int out;
            if (!q.dequeue(out)) cout << "Circular Queue is empty.\n";
            else cout << "Dequeued: " << out << '\n';
        } else if (opt == 3) cout << (q.isEmpty()? "Empty\n":"Not empty\n");
        else if (opt == 4) cout << (q.isFull()? "Full\n":"Not full\n");
        else if (opt == 5) {
            int out; if (!q.peek(out)) cout << "Circular Queue is empty.\n"; else cout << "Front: " << out << '\n';
        } else if (opt == 6) q.display();
        else cout << "Invalid\n";
    }
}

void demoInterleaveQueue() {
    cout << "Enter number of elements (even preferred): ";
    int n; cin >> n;
    queue<int> q;
    cout << "Enter " << n << " elements separated by space:\n";
    for (int i = 0; i < n; ++i) { int x; cin >> x; q.push(x); }
    cout << "Before: ";
    queue<int> tmp = q;
    while (!tmp.empty()) { cout << tmp.front() << (tmp.size()==1?'\n':' '); tmp.pop(); }
    interleaveQueue(q);
    cout << "After interleave: ";
    while (!q.empty()) { cout << q.front() << (q.size()==1?'\n':' '); q.pop(); }
}

void demoFirstNonRepeating() {
    cout << "Enter characters separated by spaces (single letters). End input with newline.\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear rest
    string line;
    getline(cin, line);
    // parse chars (skip spaces). Accept tokens; first char of each token used.
    vector<char> inputs;
    istringstream iss(line);
    string token;
    while (iss >> token) {
        if (!token.empty()) inputs.push_back(token[0]);
    }
    auto outputs = firstNonRepeatingChars(inputs);
    cout << "Outputs (first non-repeating after each input):\n";
    for (size_t i = 0; i < outputs.size(); ++i) {
        cout << outputs[i] << (i+1==outputs.size()?'\n':' ');
    }
}

void demoStackUsingQueues() {
    StackTwoQueues s2;
    StackOneQueue s1;
    while (true) {
        cout << "\n--- Stack via Queues Menu ---\n"
             << "1. Two-queue stack: push\n2. Two-queue stack: pop\n3. Two-queue stack: peek/display\n"
             << "4. One-queue stack: push\n5. One-queue stack: pop\n6. One-queue stack: peek/display\n0. return\nChoose: ";
        int opt; if (!(cin >> opt)) { cin.clear(); cin.ignore(1<<20,'\n'); continue; }
        if (opt == 0) break;
        if (opt == 1) {
            int x; cout << "Enter value to push: "; cin >> x; s2.push(x); cout << "Pushed\n";
        } else if (opt == 2) {
            int out; if (!s2.pop(out)) cout << "Stack empty\n"; else cout << "Popped: " << out << '\n';
        } else if (opt == 3) {
            int out; if (!s2.peek(out)) cout << "Empty\n"; else cout << "Top: " << out << '\n';
            s2.display();
        } else if (opt == 4) {
            int x; cout << "Enter value to push: "; cin >> x; s1.push(x); cout << "Pushed\n";
        } else if (opt == 5) {
            int out; if (!s1.pop(out)) cout << "Stack empty\n"; else cout << "Popped: " << out << '\n';
        } else if (opt == 6) {
            int out; if (!s1.peek(out)) cout << "Empty\n"; else cout << "Top: " << out << '\n';
            s1.display();
        } else cout << "Invalid\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << "=== Queues and Stack-via-Queues Toolkit ===\n";
    while (true) {
        cout << "\nMain Menu:\n"
             << "1. Simple Queue (array) operations\n"
             << "2. Circular Queue (array) operations\n"
             << "3. Interleave first half with second half of a queue\n"
             << "4. First non-repeating character in a stream (queue-based)\n"
             << "5. Stack using queues (two-queue and single-queue implementations)\n"
             << "0. Exit\nChoose: ";
        int choice;
        if (!(cin >> choice)) { cin.clear(); cin.ignore(1<<20,'\n'); continue; }
        if (choice == 0) { cout << "Bye!\n"; break; }
        if (choice == 1) simpleQueueMenu();
        else if (choice == 2) circularQueueMenu();
        else if (choice == 3) demoInterleaveQueue();
        else if (choice == 4) {
            cout << "Note: input like: a a b c (space separated). Press ENTER when done.\n";
            demoFirstNonRepeating();
        }
        else if (choice == 5) demoStackUsingQueues();
        else cout << "Invalid choice\n";
    }
    return 0;
}
