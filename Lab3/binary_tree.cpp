#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>
#include <cmath>
using namespace std;

// ฟังก์ชันตรวจว่าเป็น Operator ไหม
bool isOperator(const string& c) {
    return (c == "+" || c == "-" || c == "*" || c == "/" || c == "^");
}

// ความสำคัญของ Operator
int prec(char c) {
    if (c == '^')
        return 3; // ^ สำคัญสุด
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

// Infix → Postfix (รองรับ unary -)
vector<string> infixToPostfix(const string &s) {
    stack<char> st;
    vector<string> output;
    
    for (size_t i = 0; i < s.length();) {
        char c = s[i];

        if (isspace(c)) { i++; continue; }

        // ตรวจเจอ unary minus เช่น -3, (-2)
        if (c == '-' && 
            (i == 0 || s[i-1] == '(' || isOperator(string(1,s[i-1])))) {
            string num = "-";
            i++;
            while (i < s.length() && (isdigit(s[i]) || s[i] == '.')) {
                num += s[i];
                i++;
            }
            output.push_back(num);
        }

        else if (isdigit(c) || c == '.') {
            string num;
            while (i < s.length() && (isdigit(s[i]) || s[i] == '.')) {
                num += s[i];
                i++;
            }
            output.push_back(num);
        }

        else if (c == '(') {
            st.push(c);
            i++;
        }

        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                output.push_back(string(1, st.top()));
                st.pop();
            }
            if (!st.empty()) st.pop();
            i++;
        }

        else { // operator ปกติ
            while (!st.empty() && prec(c) <= prec(st.top())) {
                // ^ เป็น right-associative
                if (c == '^' && st.top() == '^') break;
                output.push_back(string(1, st.top()));
                st.pop();
            }
            st.push(c);
            i++;
        }
    }

    while (!st.empty()) {
        output.push_back(string(1, st.top()));
        st.pop();
    }

    return output;
}

// โครงสร้าง Node ของ Expression Tree
struct Node {
    string value;
    Node* left;
    Node* right;
    Node(string val) : value(val), left(NULL), right(NULL) {}
};

// สร้าง Expression Tree จาก Postfix
Node* buildTree(const vector<string>& postfix) {
    stack<Node*> st;
    for (auto& token : postfix) {
        if (!isOperator(token)) {
            st.push(new Node(token));
        } else {
            Node* node = new Node(token);
            node->right = st.top(); st.pop();
            node->left = st.top(); st.pop();
            st.push(node);
        }
    }
    return st.top();
}

// Traversals
void inorder(Node* root) {
    if (!root) return;
    if (root->left) cout << "(";
    inorder(root->left);
    cout << root->value;
    inorder(root->right);
    if (root->right) cout << ")";
}

void preorder(Node* root) {
    if (!root) return;
    cout << root->value << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root, vector<string>& postorder_vec) {
    if (!root) return;
    postorder(root->left, postorder_vec);
    postorder(root->right, postorder_vec);
    postorder_vec.push_back(root->value);
    cout << root->value << " ";
}

// คำนวณจาก Postfix
double evaluatePostOrder(const vector<string> &postfix) {
    stack<double> st;
    for (auto &token : postfix) {
        if (!isOperator(token)) {
            st.push(stod(token));
        } else {
            double b = st.top(); st.pop();
            double a = st.top(); st.pop();
            if (token == "+") st.push(a + b);
            else if (token == "-") st.push(a - b);
            else if (token == "*") st.push(a * b);
            else if (token == "/") st.push(a / b);
            else if (token == "^") st.push(pow(a, b));
        }
    }
    return st.top();
}

int main() {
    string expr;
    vector<string> postOrder;
    cout << "Enter arithmetic expression (example: (5+3)-2 ): ";
    getline(cin, expr);

    // 1) Infix → Postfix
    vector<string> postfix = infixToPostfix(expr);

    cout << "\nPostfix   : ";
    for (auto &p : postfix) cout << p << " ";
    cout << endl;

    // 2) สร้าง Expression Tree
    Node* root = buildTree(postfix);

    cout << "Inorder   : "; inorder(root); cout << endl;
    cout << "Preorder  : "; preorder(root); cout << endl;
    cout << "Postorder : "; postorder(root, postOrder); cout << endl;

    // 3) คำนวณผลลัพธ์จาก Postorder
    double result = evaluatePostOrder(postOrder);
    cout << "\nResult = " << result << endl;

    return 0;
}