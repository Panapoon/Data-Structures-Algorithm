#include <bits/stdc++.h>
using namespace std;

int prec(char c) {
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

// ฟังก์ชันแปลง Infix → Postfix
vector<string> infixToPostfix(const string &s) {
    stack<char> st;
    vector<string> output;  // postfix ที่เป็น token
    
    for (size_t i = 0; i < s.length();) {
        char c = s[i];

        // ข้ามช่องว่าง
        if (isspace(c)) { i++; continue; }

        // ถ้าเป็นตัวเลข (รองรับหลายหลักและทศนิยม)
        if (isdigit(c) || c == '.') {
            string num;
            while (i < s.length() && (isdigit(s[i]) || s[i] == '.')) {
                num += s[i];
                i++;
            }
            output.push_back(num);
        }
        // วงเล็บเปิด
        else if (c == '(') {
            st.push(c);
            i++;
        }
        // วงเล็บปิด
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                output.push_back(string(1, st.top()));
                st.pop();
            }
            if (!st.empty()) st.pop(); // pop '('
            i++;
        }
        // ตัวดำเนินการ
        else {
            while (!st.empty() && prec(c) <= prec(st.top())) {
                // กรณี ^ เป็น right-associative → ต้องหยุดถ้า prec เท่ากัน
                if (c == '^' && st.top() == '^') break;
                output.push_back(string(1, st.top()));
                st.pop();
            }
            st.push(c);
            i++;
        }
    }

    // เอาตัวที่เหลือใน stack ออกมา
    while (!st.empty()) {
        output.push_back(string(1, st.top()));
        st.pop();
    }

    return output;
}

// ฟังก์ชันคำนวณ Postfix
double evaluatePostfix(const vector<string> &postfix) {
    stack<string> calculate;
    stack<double> st;
    double Result;
    for (size_t i = 0; i < postfix.size();i++){
        if(isdigit(postfix[i][postfix[i].length() - 1]) || postfix[i][0] == '.') {calculate.push(postfix[i]);}
        else {
            string op = postfix[i];
            double last_number = stod(calculate.top()); calculate.pop();
            double before_last_number = stod(calculate.top()); calculate.pop();
            if (op == "+"){
                calculate.push(to_string(before_last_number + last_number));
            }
            else if (op == "-"){
                calculate.push(to_string(before_last_number - last_number));
            }
            else if (op == "*"){
                calculate.push(to_string(before_last_number * last_number));
            }
            else if (op == "/"){
                calculate.push(to_string(before_last_number / last_number));
            }
            else if (op == "^"){
                calculate.push(to_string(pow(before_last_number, last_number)));
            }
        }
    }
    if (calculate.size() == 0) cout << "bruh";
    Result = stod(calculate.top());
    return Result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string exp;
    cout << "Enter expression (infix): ";
    getline(cin, exp);

    try {
        // 1) Infix → Postfix
        auto postfix = infixToPostfix(exp);

        cout << "Postfix expression: ";
        for (auto &tok : postfix) cout << tok << " , ";
        cout << "\n";

        // 2) Evaluate Postfix
        double ans = evaluatePostfix(postfix);
        cout << "Result = " << fixed << setprecision(10) << ans << "\n";
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}