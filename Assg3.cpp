// stack_menu.cpp
#include <bits/stdc++.h>
using namespace std;

/*
  Generic fixed-capacity stack implemented on top of an array.
  - Templated to hold different types (char, int, string, etc.)
  - Capacity specified at construction.
*/
template<typename T>
class ArrayStack {
    T *arr;
    int topIndex;
    int capacity;
public:
    ArrayStack(int cap = 100) : topIndex(-1), capacity(cap) {
        arr = new T[capacity];
    }
    ~ArrayStack() { delete[] arr; }

    bool push(const T &val) {
        if (isFull()) return false;
        arr[++topIndex] = val;
        return true;
    }
    bool pop(T &out) {
        if (isEmpty()) return false;
        out = arr[topIndex--];
        return true;
    }
    bool peek(T &out) const {
        if (isEmpty()) return false;
        out = arr[topIndex];
        return true;
    }
    bool isEmpty() const { return topIndex == -1; }
    bool isFull() const { return topIndex == capacity - 1; }
    int size() const { return topIndex + 1; }
    void display() const {
        if (isEmpty()) {
            cout << "Stack is empty.\n";
            return;
        }
        cout << "Stack (top -> bottom): ";
        for (int i = topIndex; i >= 0; --i) cout << arr[i] << (i ? " " : "");
        cout << "\n";
    }
};

/* -------------------- Task 2: Reverse string using stack -------------------- */
string reverseUsingStack(const string &s) {
    ArrayStack<char> st((int)s.size());
    for (char c : s) st.push(c);
    string out;
    out.reserve(s.size());
    char c;
    while (st.pop(c)) out.push_back(c);
    return out;
}

/* -------------------- Task 3: Balanced parentheses -------------------- */
/* Supports (), {}, [] */
bool isMatchingPair(char open, char close) {
    return (open == '(' && close == ')')
        || (open == '{' && close == '}')
        || (open == '[' && close == ']');
}

bool areParenthesesBalanced(const string &expr) {
    ArrayStack<char> st((int)expr.size());
    for (char ch : expr) {
        if (ch == '(' || ch == '{' || ch == '[') st.push(ch);
        else if (ch == ')' || ch == '}' || ch == ']') {
            char topc;
            if (!st.pop(topc)) return false; // nothing to match
            if (!isMatchingPair(topc, ch)) return false;
        }
    }
    return st.isEmpty();
}

/* -------------------- Task 4: Infix to Postfix -------------------- */
/* We will convert to space-separated postfix tokens. Supports:
   - multi-digit integers
   - variable names (alphanumeric sequences)
   - operators + - * / ^ and parentheses ()
*/
int precedence(char op) {
    if (op == '^') return 4;
    if (op == '*' || op == '/') return 3;
    if (op == '+' || op == '-') return 2;
    return 0;
}

bool isRightAssociative(char op) {
    return (op == '^');
}

// Convert infix (string) to postfix (string with space-separated tokens)
string infixToPostfix(const string &infix) {
    // Use ArrayStack<char> for operators
    ArrayStack<char> st((int)infix.size());
    string out;
    int n = (int)infix.size();
    for (int i = 0; i < n; ) {
        char c = infix[i];

        // Skip spaces
        if (isspace(c)) { ++i; continue; }

        // If digit -> parse full number (handles multi-digit)
        if (isdigit(c)) {
            string num;
            while (i < n && isdigit(infix[i])) { num.push_back(infix[i]); ++i; }
            out += num;
            out.push_back(' ');
            continue;
        }

        // If alphabetic -> parse variable name (letters/digits)
        if (isalpha(c)) {
            string name;
            while (i < n && (isalnum(infix[i]) || infix[i]=='_')) { name.push_back(infix[i]); ++i; }
            out += name;
            out.push_back(' ');
            continue;
        }

        // If '(', push to stack
        if (c == '(') { st.push(c); ++i; continue; }

        // If ')', pop until '('
        if (c == ')') {
            char topc;
            while (st.pop(topc)) {
                if (topc == '(') break;
                out.push_back(topc);
                out.push_back(' ');
            }
            ++i;
            continue;
        }

        // Operator
        if (strchr("+-*/^", c)) {
            char op = c;
            char topc;
            while (!st.isEmpty() && st.peek(topc) && topc != '(') {
                int pTop = precedence(topc);
                int pOp = precedence(op);
                // While (top has higher prec) OR (same prec and op is left-assoc), pop
                if (pTop > pOp || (pTop == pOp && !isRightAssociative(op))) {
                    st.pop(topc);
                    out.push_back(topc);
                    out.push_back(' ');
                } else break;
            }
            st.push(op);
            ++i;
            continue;
        }

        // Unknown char: skip (or we could error)
        ++i;
    }

    // Pop remaining operators
    char topc;
    while (st.pop(topc)) {
        if (topc == '(' || topc == ')') {
            // mismatched parentheses; return empty string to indicate error
            return string();
        }
        out.push_back(topc);
        out.push_back(' ');
    }

    // Trim trailing spaces
    while (!out.empty() && isspace(out.back())) out.pop_back();
    return out;
}

/* -------------------- Task 5: Evaluate Postfix -------------------- */
/* Expects postfix with tokens separated by spaces. Supports integers and operators + - * / ^.
   Division is integer division (like C++ integer /). */
long long evalPostfix(const string &postfix, bool &ok) {
    ok = true;
    istringstream iss(postfix);
    string token;
    ArrayStack<long long> st(1000);
    while (iss >> token) {
        // If token is a number (possibly negative)
        bool isNumber = false;
        // check for optional leading '-' for negative numbers
        int idx = 0;
        if (token.size() > 0 && (token[0] == '-' || token[0] == '+')) idx = 1;
        isNumber = idx < (int)token.size();
        for (int i = idx; i < (int)token.size() && isNumber; ++i) {
            if (!isdigit(token[i])) isNumber = false;
        }
        if (isNumber) {
            long long val = stoll(token);
            st.push(val);
        } else if (token.size() == 1 && strchr("+-*/^", token[0])) {
            long long b, a;
            if (!st.pop(b) || !st.pop(a)) { ok = false; return 0; } // insufficient operands
            long long res = 0;
            char op = token[0];
            if (op == '+') res = a + b;
            else if (op == '-') res = a - b;
            else if (op == '*') res = a * b;
            else if (op == '/') {
                if (b == 0) { ok = false; return 0; } // divide by zero
                res = a / b;
            } else if (op == '^') {
                // integer power (beware large exponents)
                if (b < 0) { ok = false; return 0; } // negative exponent unsupported for integer
                long long r = 1;
                for (long long i = 0; i < b; ++i) r *= a;
                res = r;
            }
            st.push(res);
        } else {
            ok = false;
            return 0; // unknown token
        }
    }
    long long finalVal;
    if (!st.pop(finalVal) || !st.isEmpty()) { ok = false; return 0; }
    return finalVal;
}

/* -------------------- Menu and demos -------------------- */
void menuStackDemo() {
    const int CAP = 100;
    ArrayStack<int> st(CAP);
    while (true) {
        cout << "\n=== STACK (array) MENU ===\n"
             << "1. push()\n2. pop()\n3. isEmpty()\n4. isFull()\n5. display()\n6. peek()\n0. Return\nChoose option: ";
        int opt; if (!(cin >> opt)) { cin.clear(); cin.ignore(1<<20,'\n'); continue; }
        if (opt == 0) break;
        if (opt == 1) {
            int x; cout << "Enter integer to push: "; cin >> x;
            if (!st.push(x)) cout << "Stack overflow (isFull == true).\n";
            else cout << "Pushed " << x << '\n';
        } else if (opt == 2) {
            int val;
            if (!st.pop(val)) cout << "Stack underflow (isEmpty == true).\n";
            else cout << "Popped: " << val << '\n';
        } else if (opt == 3) cout << (st.isEmpty() ? "Stack is empty.\n" : "Stack is not empty.\n");
        else if (opt == 4) cout << (st.isFull() ? "Stack is full.\n" : "Stack is not full.\n");
        else if (opt == 5) st.display();
        else if (opt == 6) {
            int val;
            if (!st.peek(val)) cout << "Stack is empty; nothing to peek.\n";
            else cout << "Top element: " << val << '\n';
        } else cout << "Invalid option.\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (true) {
        cout << "\n==== MAIN MENU ====\n"
             << "1. Stack (array) operations (menu-driven)\n"
             << "2. Reverse a string using STACK\n"
             << "3. Check balanced parentheses\n"
             << "4. Convert Infix to Postfix\n"
             << "5. Evaluate Postfix expression\n"
             << "0. Exit\n"
             << "Choose option: ";
        int choice;
        if (!(cin >> choice)) { cin.clear(); cin.ignore(1<<20,'\n'); continue; }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear rest of line
        if (choice == 0) { cout << "Goodbye!\n"; break; }

        if (choice == 1) {
            menuStackDemo();
        } else if (choice == 2) {
            cout << "Enter string to reverse: ";
            string s;
            getline(cin, s);
            cout << "Reversed: " << reverseUsingStack(s) << "\n";
        } else if (choice == 3) {
            cout << "Enter expression to check (parentheses only): ";
            string expr;
            getline(cin, expr);
            bool ok = areParenthesesBalanced(expr);
            cout << (ok ? "Balanced\n" : "Not Balanced\n");
        } else if (choice == 4) {
            cout << "Enter infix expression (supports multi-digit numbers and variables):\n";
            cout << "Example: (3+4)*5 - or - a+b*(c^d-e)^(f+g*h)-i\n";
            string infix;
            getline(cin, infix);
            string postfix = infixToPostfix(infix);
            if (postfix.empty()) cout << "Error: mismatched parentheses or invalid expression.\n";
            else cout << "Postfix: " << postfix << "\n";
        } else if (choice == 5) {
            cout << "Enter postfix expression (space-separated tokens):\n";
            cout << "Examples:\n  '3 4 + 5 *' (=> (3+4)*5)\n  '10 2 8 * + 3 -' \n";
            string postfix;
            getline(cin, postfix);
            bool ok;
            long long result = evalPostfix(postfix, ok);
            if (!ok) cout << "Error evaluating postfix (invalid tokens, divide by zero, or stack error).\n";
            else cout << "Result = " << result << "\n";
        } else {
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}
