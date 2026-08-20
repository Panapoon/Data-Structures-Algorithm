#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9; // ค่ามาก ๆ แทนว่าไม่มีเส้นทาง

// ------------------------------------------------------
// ฟังก์ชันอ่านข้อมูลกราฟ (ไม่มีทิศทาง)
// ------------------------------------------------------
void readGraph(vector<vector<int>> &dist, int n, int m) {
    for (int i = 1; i <= n; i++)
        dist[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        // ถ้ามีหลายเส้นให้เลือกอันที่เสียงเบากว่า
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);
    }
}

// ------------------------------------------------------
// ฟังก์ชัน Floyd–Warshall (minimize the maximum edge)
// ------------------------------------------------------
void floydMinMax(vector<vector<int>> &dist, int n) {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // ถ้ามีทางผ่าน k ให้ดูว่าเสียงมากสุดระหว่างเส้นทาง i-k-j เป็นเท่าไร
                int throughK = max(dist[i][k], dist[k][j]);
                // ถ้าเสียงนี้เบากว่าค่าเดิม ให้เลือกอันนี้แทน
                dist[i][j] = min(dist[i][j], throughK);
            }
        }
    }
}

// ------------------------------------------------------
// ฟังก์ชันตอบคำถาม (query)
// ------------------------------------------------------
void answerQueries(const vector<vector<int>> &dist, int q) {
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        if (dist[a][b] == INF)
            cout << "no path\n";
        else
            cout << dist[a][b] << "\n";
    }
}

// ------------------------------------------------------
// main()
// ------------------------------------------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));

    readGraph(dist, n, m);
    floydMinMax(dist, n);
    answerQueries(dist, q);

    return 0;
}
