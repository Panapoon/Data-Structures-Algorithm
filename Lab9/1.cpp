#include <bits/stdc++.h>
using namespace std;

// ------------------------------------------
// ฟังก์ชัน DFS สำหรับตรวจว่ากราฟเชื่อมถึงกันไหม
// ------------------------------------------
void dfs(int u, const vector<vector<int>>& adj, vector<bool>& visited) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v])
            dfs(v, adj, visited);
    }
}

// ------------------------------------------
// โปรแกรมหลัก
// ------------------------------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int caseNum = 1; // ใช้นับกรณี
    while (true) {
        int N, M;
        cin >> N >> M;
        if (N == 0 && M == 0) break; // จบข้อมูล

        // สร้าง adjacency list
        vector<vector<int>> adj(N + 1);
        for (int i = 0; i < M; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            if (c == 1) { // ใช้เฉพาะถนนที่ใช้ได้
                adj[a].push_back(b);
                adj[b].push_back(a);
            }
        }

        // เริ่ม DFS จากเมือง 1
        vector<bool> visited(N + 1, false);
        dfs(1, adj, visited);

        // ตรวจว่าครบทุกเมืองไหม
        bool connected = true;
        for (int i = 1; i <= N; i++) {
            if (!visited[i]) {
                connected = false;
                break;
            }
        }

        // แสดงผลพร้อมหมายเลขกรณี
        cout << "Case " << caseNum << ": " << (connected ? 1 : 0) << "\n";
        caseNum++;
    }

    return 0;
}
