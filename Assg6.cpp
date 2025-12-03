#include <iostream>
#include <string>
using namespace std;

struct DNode {
    int data;
    DNode* prev;
    DNode* next;
};

struct CNode {
    int data;
    CNode* next;
};

struct DCharNode {
    char data;
    DCharNode* prev;
    DCharNode* next;
};

struct SNode {
    int data;
    SNode* next;
};

DNode* createDNode(int x) {
    DNode* t = new DNode;
    t->data = x;
    t->prev = t->next = nullptr;
    return t;
}

CNode* createCNode(int x) {
    CNode* t = new CNode;
    t->data = x;
    t->next = nullptr;
    return t;
}

DCharNode* createDCharNode(char c) {
    DCharNode* t = new DCharNode;
    t->data = c;
    t->prev = t->next = nullptr;
    return t;
}

SNode* createSNode(int x) {
    SNode* t = new SNode;
    t->data = x;
    t->next = nullptr;
    return t;
}

void insertFirstD(DNode*& head, int x) {
    DNode* node = createDNode(x);
    if (!head) {
        head = node;
        return;
    }
    node->next = head;
    head->prev = node;
    head = node;
}

void insertLastD(DNode*& head, int x) {
    DNode* node = createDNode(x);
    if (!head) {
        head = node;
        return;
    }
    DNode* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = node;
    node->prev = temp;
}

DNode* searchD(DNode* head, int key) {
    while (head) {
        if (head->data == key) return head;
        head = head->next;
    }
    return nullptr;
}

void insertAfterD(DNode* head, int key, int x) {
    DNode* pos = searchD(head, key);
    if (!pos) return;
    DNode* node = createDNode(x);
    node->next = pos->next;
    node->prev = pos;
    if (pos->next) pos->next->prev = node;
    pos->next = node;
}

void insertBeforeD(DNode*& head, int key, int x) {
    if (!head) return;
    if (head->data == key) {
        insertFirstD(head, x);
        return;
    }
    DNode* temp = head;
    while (temp && temp->data != key) temp = temp->next;
    if (!temp) return;
    DNode* node = createDNode(x);
    DNode* p = temp->prev;
    node->next = temp;
    node->prev = p;
    p->next = node;
    temp->prev = node;
}

void deleteNodeD(DNode*& head, int key) {
    if (!head) return;
    DNode* temp = head;
    while (temp && temp->data != key) temp = temp->next;
    if (!temp) return;
    if (temp == head) {
        head = head->next;
        if (head) head->prev = nullptr;
        delete temp;
        return;
    }
    if (temp->next) temp->next->prev = temp->prev;
    if (temp->prev) temp->prev->next = temp->next;
    delete temp;
}

void displayD(DNode* head) {
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

int sizeD(DNode* head) {
    int c = 0;
    while (head) {
        c++;
        head = head->next;
    }
    return c;
}

void insertFirstC(CNode*& head, int x) {
    CNode* node = createCNode(x);
    if (!head) {
        head = node;
        node->next = head;
        return;
    }
    CNode* temp = head;
    while (temp->next != head) temp = temp->next;
    node->next = head;
    temp->next = node;
    head = node;
}

void insertLastC(CNode*& head, int x) {
    CNode* node = createCNode(x);
    if (!head) {
        head = node;
        node->next = head;
        return;
    }
    CNode* temp = head;
    while (temp->next != head) temp = temp->next;
    temp->next = node;
    node->next = head;
}

CNode* searchC(CNode* head, int key) {
    if (!head) return nullptr;
    CNode* temp = head;
    do {
        if (temp->data == key) return temp;
        temp = temp->next;
    } while (temp != head);
    return nullptr;
}

void insertAfterC(CNode* head, int key, int x) {
    if (!head) return;
    CNode* pos = searchC(head, key);
    if (!pos) return;
    CNode* node = createCNode(x);
    node->next = pos->next;
    pos->next = node;
}

void insertBeforeC(CNode*& head, int key, int x) {
    if (!head) return;
    if (head->data == key) {
        insertFirstC(head, x);
        return;
    }
    CNode* prev = nullptr;
    CNode* curr = head;
    do {
        if (curr->data == key) break;
        prev = curr;
        curr = curr->next;
    } while (curr != head);
    if (curr == head) return;
    CNode* node = createCNode(x);
    node->next = curr;
    prev->next = node;
}

void deleteNodeC(CNode*& head, int key) {
    if (!head) return;
    CNode* curr = head;
    CNode* prev = nullptr;
    do {
        if (curr->data == key) break;
        prev = curr;
        curr = curr->next;
    } while (curr != head);
    if (curr->data != key) return;
    if (curr == head && curr->next == head) {
        delete curr;
        head = nullptr;
        return;
    }
    if (curr == head) {
        CNode* tail = head;
        while (tail->next != head) tail = tail->next;
        head = head->next;
        tail->next = head;
        delete curr;
        return;
    }
    prev->next = curr->next;
    delete curr;
}

void displayC(CNode* head) {
    if (!head) {
        cout << endl;
        return;
    }
    CNode* temp = head;
    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);
    cout << endl;
}

void displayCWithHeadRepeat(CNode* head) {
    if (!head) {
        cout << endl;
        return;
    }
    CNode* temp = head;
    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);
    cout << head->data << endl;
}

int sizeC(CNode* head) {
    if (!head) return 0;
    int c = 0;
    CNode* temp = head;
    do {
        c++;
        temp = temp->next;
    } while (temp != head);
    return c;
}

void insertLastDChar(DCharNode*& head, char c) {
    DCharNode* node = createDCharNode(c);
    if (!head) {
        head = node;
        return;
    }
    DCharNode* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = node;
    node->prev = temp;
}

bool isPalindromeDChar(DCharNode* head) {
    if (!head || !head->next) return true;
    DCharNode* left = head;
    DCharNode* right = head;
    while (right->next) right = right->next;
    while (left != right && right->next != left) {
        if (left->data != right->data) return false;
        left = left->next;
        right = right->prev;
    }
    return true;
}

bool isCircular(SNode* head) {
    if (!head) return false;
    SNode* temp = head->next;
    while (temp && temp != head) temp = temp->next;
    return temp == head;
}

int main() {
    DNode* dhead = nullptr;
    CNode* chead = nullptr;
    int mainChoice;
    while (true) {
        cout << "\n1 Doubly Linked List Ops\n2 Circular Linked List Ops\n3 DLL Palindrome (chars)\n4 Check if Linked List is Circular\n5 Exit\n";
        cin >> mainChoice;
        if (mainChoice == 1) {
            int ch;
            while (true) {
                cout << "\nDoubly List: 1 InsertFirst 2 InsertLast 3 InsertAfter 4 InsertBefore 5 Delete 6 Search 7 Display 8 Size 9 Back\n";
                cin >> ch;
                if (ch == 9) break;
                int x,k;
                DNode* p;
                if (ch == 1) { cin >> x; insertFirstD(dhead, x); }
                else if (ch == 2) { cin >> x; insertLastD(dhead, x); }
                else if (ch == 3) { cin >> k >> x; insertAfterD(dhead, k, x); }
                else if (ch == 4) { cin >> k >> x; insertBeforeD(dhead, k, x); }
                else if (ch == 5) { cin >> x; deleteNodeD(dhead, x); }
                else if (ch == 6) { cin >> x; p = searchD(dhead, x); cout << (p ? 1 : 0) << endl; }
                else if (ch == 7) { displayD(dhead); }
                else if (ch == 8) { cout << sizeD(dhead) << endl; }
            }
        } else if (mainChoice == 2) {
            int ch;
            while (true) {
                cout << "\nCircular List: 1 InsertFirst 2 InsertLast 3 InsertAfter 4 InsertBefore 5 Delete 6 Search 7 Display 8 DisplayWithHeadRepeat 9 Size 10 Back\n";
                cin >> ch;
                if (ch == 10) break;
                int x,k;
                CNode* p;
                if (ch == 1) { cin >> x; insertFirstC(chead, x); }
                else if (ch == 2) { cin >> x; insertLastC(chead, x); }
                else if (ch == 3) { cin >> k >> x; insertAfterC(chead, k, x); }
                else if (ch == 4) { cin >> k >> x; insertBeforeC(chead, k, x); }
                else if (ch == 5) { cin >> x; deleteNodeC(chead, x); }
                else if (ch == 6) { cin >> x; p = searchC(chead, x); cout << (p ? 1 : 0) << endl; }
                else if (ch == 7) { displayC(chead); }
                else if (ch == 8) { displayCWithHeadRepeat(chead); }
                else if (ch == 9) { cout << sizeC(chead) << endl; }
            }
        } else if (mainChoice == 3) {
            string s;
            cin >> s;
            DCharNode* headChar = nullptr;
            for (char c : s) insertLastDChar(headChar, c);
            cout << (isPalindromeDChar(headChar) ? 1 : 0) << endl;
        } else if (mainChoice == 4) {
            int n;
            cin >> n;
            if (n <= 0) {
                cout << 0 << endl;
                continue;
            }
            SNode* head = nullptr;
            SNode* tail = nullptr;
            for (int i = 0; i < n; i++) {
                int x;
                cin >> x;
                SNode* node = createSNode(x);
                if (!head) {
                    head = tail = node;
                } else {
                    tail->next = node;
                    tail = node;
                }
            }
            int makeCirc;
            cin >> makeCirc;
            if (makeCirc == 1 && tail) tail->next = head;
            cout << (isCircular(head) ? 1 : 0) << endl;
        } else if (mainChoice == 5) {
            break;
        }
    }
    return 0;
}
