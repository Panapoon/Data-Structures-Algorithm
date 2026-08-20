#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

// -----------------------------------------
// ตรวจว่าใส่ v ต่อท้ายได้ไหม (ไม่ทำให้เกิดเลขคณิต 3 พจน์)
// -----------------------------------------
bool ok_to_append(const vector<int>& seq, int v) {
    int m = seq.size();
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            if (seq[i] + v == 2 * seq[j])
                return false;
        }
    }
    return true;
}

// -----------------------------------------
// Backtracking DFS (มี start/end)
// -----------------------------------------
bool dfs(int start, int end, vector<bool>& used, vector<int>& seq) {
    // ถ้าครบทุกตัวแล้ว → ตรวจว่าตัวสุดท้ายตรงกับ end ไหม
    if ((int)seq.size() == end - start + 1)
        return seq.back() == end;

    for (int v = start; v <= end; v++) {
        if (used[v - start]) continue;
        if (ok_to_append(seq, v)) {
            used[v - start] = true;
            seq.push_back(v);

            if (dfs(start, end, used, seq))
                return true;

            seq.pop_back();
            used[v - start] = false;
        }
    }
    return false;
}

// -----------------------------------------
// main function
// -----------------------------------------
vector<int> beautiful_backtracking(int start, int end) {
    int n = end - start + 1;
    vector<bool> used(n, false);
    vector<int> seq;

    // เริ่มต้นด้วย start เสมอ
    seq.push_back(start);
    used[0] = true;

    if (dfs(start, end, used, seq))
        return seq;
    throw runtime_error("No ordering found.");
}

// -----------------------------------------
// main program
// -----------------------------------------
int main() {
    int start, end;
    cin >> start >> end;

    vector<int> ans = beautiful_backtracking(start, end);
    for (int i = 0; i < (int)ans.size(); i++) {
        cout << ans[i];
        if (i + 1 < (int)ans.size())
            cout << " ";
    }
    cout << "\n";
    return 0;
}
