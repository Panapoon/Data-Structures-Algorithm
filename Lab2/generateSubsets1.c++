#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

// ฟังก์ชันตัดสตริงออกเป็นสมาชิกของเซต
vector<string> parseSet(string input) {
    vector<string> elements;
    string temp;
    int brace = 0;

    for (char c : input) {
        if (c == '{') {
            if (brace > 0) temp += c;
            brace++;
        } else if (c == '}') {
            brace--;
            if (brace > 0) temp += c;
            else if (!temp.empty()) {
                elements.push_back("{" + temp + "}");
                temp.clear();
            }
        } else if (c == ',' && brace == 0) {
            if (!temp.empty()) {
                elements.push_back(temp);
                temp.clear();
            }
        } else {
            temp += c;
        }
    }
    if (!temp.empty()) elements.push_back(temp);

    // ลบ space ออก
    for (auto &s : elements) {
        s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
    }

    // ลบสมาชิกซ้ำออก (ใช้ set)
    vector<string> uniqueElements;
    set<string> seen;
    for (auto &s : elements) {
        if (seen.insert(s).second) { // ถ้าไม่ซ้ำ
            uniqueElements.push_back(s);
        }
    }

    return uniqueElements;
}

int main() {
    string input;
    cout << "Enter set T (e.g. {1,2,{2}}): ";
    getline(cin, input);

    // ตัด {} ออก
    if (input.front() == '{' && input.back() == '}')
        input = input.substr(1, input.size() - 2);

    // แปลงเป็น vector
    vector<string> T = parseSet(input);
    int n = T.size();

    cout << "\nAll subsets of T are:\n";
    int total = 1 << n; // 2^n

    for (int mask = 0; mask < total; mask++) {
        cout << "{";
        bool first = true;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                if (!first) cout << ", ";
                cout << T[i];
                first = false;
            }
        }
        cout << "}" << endl;
    }
    return 0;
}
