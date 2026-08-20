#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// ---------------- Node ----------------
struct Node {
    string value;
    Node* left;
    Node* right;
    Node(string val) : value(val), left(nullptr), right(nullptr) {}
};

// ---------------- Parser ----------------
class Parser {
    string s;
    size_t pos;
public:
    Parser(const string& str) : s(str), pos(0) {}

    // skip spaces
    void skip() { while(pos < s.size() && isspace(s[pos])) pos++; }

    // parse a number
    Node* parseNumber() {
        skip();
        string num;
        while(pos < s.size() && (isdigit(s[pos]) || s[pos]=='.')) {
            num += s[pos++];
        }
        return new Node(num);
    }

    // parse factor: number | '(' expr ')' | factor ^ factor
    Node* parseFactor() {
        skip();
        Node* node = nullptr;
        if(s[pos] == '(') {
            pos++; // skip '('
            node = parseExpression();
            skip();
            if(s[pos] == ')') pos++; // skip ')'
        } else {
            node = parseNumber();
        }

        skip();
        // handle ^
        while(pos < s.size() && s[pos] == '^') {
            char op = s[pos++];
            Node* newNode = new Node(string(1, op));
            newNode->left = node;
            newNode->right = parseFactor(); // right-associative
            node = newNode;
        }
        return node;
    }

    // parse term: factor * factor / factor ...
    Node* parseTerm() {
        Node* node = parseFactor();
        skip();
        while(pos < s.size() && (s[pos]=='*' || s[pos]=='/')) {
            char op = s[pos++];
            Node* newNode = new Node(string(1, op));
            newNode->left = node;
            newNode->right = parseFactor();
            node = newNode;
        }
        return node;
    }

    // parse expression: term + term - term ...
    Node* parseExpression() {
        Node* node = parseTerm();
        skip();
        while(pos < s.size() && (s[pos]=='+' || s[pos]=='-')) {
            char op = s[pos++];
            Node* newNode = new Node(string(1, op));
            newNode->left = node;
            newNode->right = parseTerm();
            node = newNode;
        }
        return node;
    }
};

// ---------------- Traversals ----------------
void inorder(Node* root) {
    if(!root) return;
    if(root->left || root->right) cout << "(";
    inorder(root->left);
    cout << root->value;
    inorder(root->right);
    if(root->left || root->right) cout << ")";
}

void preorder(Node* root) {
    if(!root) return;
    cout << root->value << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if(!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->value << " ";
}

// ---------------- Main ----------------
int main() {
    string expr;
    cout << "Enter arithmetic expression: ";
    getline(cin, expr);

    Parser parser(expr);
    Node* root = parser.parseExpression();

    cout << "Inorder   : "; inorder(root); cout << endl;
    cout << "Preorder  : "; preorder(root); cout << endl;
    cout << "Postorder : "; postorder(root); cout << endl;

    return 0;
}
