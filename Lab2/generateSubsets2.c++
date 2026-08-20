#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <stack>
#include <queue>
using namespace std;

vector<string> parseSet(string input) {
    vector<string> elements;
    string temp;
    int brace = 0;

    for (char c : input) {
        if (isspace(c)) continue;

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

    // ลบสมาชิกซ้ำ
    vector<string> uniqueElements;
    set<string> seen;
    for (auto &s : elements) {
        if (seen.insert(s).second) {
            uniqueElements.push_back(s);
        }
    }

    return uniqueElements;
}

void generateSubsetsStack(vector<string>& T) {
    cout << "\nSubsets using Stack (DFS order):\n";
    stack<pair<vector<string>, int>> st;
    st.push({{}, 0}); // เริ่มจาก subset ว่าง

    while (!st.empty()) {
        auto [subset, idx] = st.top();
        st.pop();

        // แสดง subset
        cout << "{";
        for (int i = 0; i < subset.size(); i++) {
            if (i > 0) cout << ", ";
            cout << subset[i];
        }
        cout << "}" << endl;

        // ใส่จากหลังไปหน้าเพื่อให้เรียงลำดับถูกตอน pop
        for (int i = T.size() - 1; i >= idx; i--) {
            vector<string> newSubset = subset;
            newSubset.push_back(T[i]);
            st.push({newSubset, i + 1});
        }
    }
}

void generateSubsetsQueue(vector<string>& T) {
    cout << "\nSubsets using Queue (BFS order):\n";
    queue<pair<vector<string>, int>> q;
    q.push({{}, 0}); // เริ่มจาก subset ว่าง

    while (!q.empty()) {
        auto [subset, idx] = q.front();
        q.pop();

        // แสดง subset
        cout << "{";
        for (int i = 0; i < subset.size(); i++) {
            if (i > 0) cout << ", ";
            cout << subset[i];
        }
        cout << "}" << endl;

        for (int i = idx; i < T.size(); i++) {
            vector<string> newSubset = subset;
            newSubset.push_back(T[i]);
            q.push({newSubset, i + 1});
        }
    }
}

int main() {
    string input;
    cout << "Enter set T : ";
    getline(cin, input);

    if (input.front() != '{' || input.back() != '}') {
        cout << "Error: Input is not a valid set!" << endl;
        return 1;
    }

    input = input.substr(1, input.size() - 2);
    vector<string> T = parseSet(input);

    generateSubsetsStack(T);
    generateSubsetsQueue(T);

    return 0;
}