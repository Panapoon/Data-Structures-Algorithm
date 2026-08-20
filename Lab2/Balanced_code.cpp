#include <bits/stdc++.h>
using namespace std;

bool isBalanced(const string &text) {
    stack<char> st;
    for (char c : text) {
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        }
        else if (c == ')' || c == ']' || c == '}') {
            if (st.empty()) return false;
            char top = st.top();
            st.pop();
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) {
                return false;
            }
        }
    }
    return st.empty();
}

int main() {
    string text;
    cout << "enter: ";
    cin >> text;

    if (isBalanced(text)) cout << "balance\n";
    else cout << "not balance\n";

    return 0;
}