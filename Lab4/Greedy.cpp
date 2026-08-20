#include <bits/stdc++.h>
using namespace std;

int n, k;
string arr;

// ----------- Brute force (DFS with indices) -----------
int maxPassenger = 0;
int solutionCount = 0;

void dfs(vector<int> G, vector<int> P, int count) {
    if (G.empty()) {
        if (count > maxPassenger) {
            maxPassenger = count;
            solutionCount = 1;
        } else if (count == maxPassenger) {
            solutionCount++;
        }
        return;
    }

    int g = G[0];
    vector<int> nextG(G.begin() + 1, G.end());

    // 1) กรณีไม่จับใคร
    dfs(nextG, P, count);

    // 2) กรณีจับ P ที่อยู่ในระยะ k
    for (int i = 0; i < (int)P.size(); i++) {
        if (abs(P[i] - g) <= k) {
            vector<int> nextP = P;
            nextP.erase(nextP.begin() + i);
            dfs(nextG, nextP, count + 1);
        }
    }
}

void solveBruteForce() {
    vector<int> posG, posP;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 'G') posG.push_back(i);
        if (arr[i] == 'P') posP.push_back(i);
    }

    maxPassenger = 0;
    solutionCount = 0;
    dfs(posG, posP, 0);

    cout << "Brute-force Output:\n";
    cout << solutionCount << "\n" << maxPassenger << "\n";
}

// ----------- Greedy approach (Queue) -----------
int greedySolve() {
    queue<int> qG, qP;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 'G') qG.push(i);
        else if (arr[i] == 'P') qP.push(i);

        while (!qG.empty() && !qP.empty()) {
            int g = qG.front();
            int p = qP.front();
            if (abs(g - p) <= k) {
                cnt++;
                qG.pop();
                qP.pop();
            } else if (g < p) qG.pop();
            else qP.pop();
        }
    }
    return cnt;
}

void solveGreedy() {
    int ans = greedySolve();
    cout << "Greedy Output:\n";
    cout << ans << "\n";
}

// ----------- Main -----------
int main() {
    cin >> arr;
    cin >> k;
    n = arr.size();

    solveBruteForce();
    solveGreedy();

    return 0;
}