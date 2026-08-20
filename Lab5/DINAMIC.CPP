#include <bits/stdc++.h>
using namespace std;

// ---------------- Recursive: print all ways ----------------
void rec(vector<int>& coins, int start, int remain, vector<int>& path, int &count) {
    if (remain == 0) {
        cout << "{";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1) cout << ",";
        }
        cout << "}\n";
        count++;
        return;
    }
    for (int i = start; i < (int)coins.size(); i++) {
        if (coins[i] <= remain) {
            path.push_back(coins[i]);
            rec(coins, i, remain - coins[i], path, count); // ใช้เหรียญเดิมได้ (i)
            path.pop_back();
        }
    }
}

// ---------------- Dynamic: minimum coins + all optimal  -----
int dynamicAll(vector<int>& coins, int amount, vector<vector<int>>& allSolutions) {
    const int INF = 1e9;
    vector<int> dp(amount + 1, INF);
    dp[0] = 0;

    // dp[i] = min coins to make i
    for (int i = 1; i <= amount; i++) {
        for (int c : coins) if (c <= i)
            dp[i] = min(dp[i], dp[i - c] + 1);
    }
    if (dp[amount] == INF) return -1;
    int best = dp[amount];

    // backtrack เฉพาะทางที่คงจำนวนเหรียญ = best และบังคับเรียง nondecreasing ด้วย start-index
    function<void(int,int,vector<int>&,int)> backtrack = [&](int remain, int cnt, vector<int>& path, int startIdx) {
        if (remain == 0) {
            if (cnt == best) allSolutions.push_back(path);
            return;
        }
        if (cnt >= best) return;

        for (int i = startIdx; i < (int)coins.size(); i++) {
            int c = coins[i];
            if (c <= remain && dp[remain - c] == dp[remain] - 1) {
                path.push_back(c);
                backtrack(remain - c, cnt + 1, path, i); // i (ไม่ใช่ i+1) เพื่ออนุญาตใช้ซ้ำและไม่สลับลำดับ
                path.pop_back();
            }
        }
    };

    vector<int> path;
    backtrack(amount, 0, path, 0);
    return best;
}

// ---------------- Main --------------------------------------------------------------
int main() {
    int amount;
    cout << "Enter amount: ";
    cin >> amount;
    cin.ignore();

    cout << "Enter coin values: ";
    string line; getline(cin, line);
    stringstream ss(line);

    vector<int> coins; int c;
    while (ss >> c) coins.push_back(c);
    sort(coins.begin(), coins.end()); // สำคัญ เพื่อให้ทั้ง rec/dynamic ใช้ลำดับเดียวกัน

    cout << "\n=== Recursive ways ===\n";
    vector<int> path; int count = 0;
    rec(coins, 0, amount, path, count);
    cout << "Total ways = " << count << "\n";

    cout << "\n=== Dynamic Min Coins ===\n";
    vector<vector<int>> allSolutions;
    int ans = dynamicAll(coins, amount, allSolutions);
    if (ans == -1) {
        cout << "No solution\n";
    } else {
        cout << "Minimum coins = " << ans << "\n";
        cout << "Solutions:\n";
        for (auto &sol : allSolutions) {
            cout << "{";
            for (size_t i = 0; i < sol.size(); i++) {
                cout << sol[i];
                if (i < sol.size() - 1) cout << ",";
            }
            cout << "}\n";
        }
    }
    return 0;
}
