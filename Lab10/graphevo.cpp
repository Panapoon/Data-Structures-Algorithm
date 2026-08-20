#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

// ------------------------------------
// พิมพ์ตาราง D หรือ π
// ------------------------------------
void printMatrix(const vector<vector<int>>& mat, int n, const string& title) {
    cout << "\n=== " << title << " ===\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (mat[i][j] == INF) cout << "INF\t";
            else if (mat[i][j] == -1) cout << "-\t";
            else cout << mat[i][j] << "\t";
        }
        cout << "\n";
    }
}

// ------------------------------------
// สร้างเส้นทางจริงจาก π-table
// ------------------------------------
vector<int> reconstructPath(int u, int v, const vector<vector<int>>& path) {
    if (path[u][v] == -1) return {}; // ไม่มีเส้นทาง

    vector<int> route;
    route.push_back(v);
    while (v != u) {
        v = path[u][v];
        if (v == -1) return {}; // ป้องกันหลุด loop
        route.push_back(v);
    }
    reverse(route.begin(), route.end());
    return route;
}

// ------------------------------------
// Floyd–Warshall (Minimize Max Edge)
// ------------------------------------
void floydMinMax(vector<vector<int>>& dist, vector<vector<int>>& path, int n) {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] == INF || dist[k][j] == INF) continue;

                int through = max(dist[i][k], dist[k][j]);
                if (through < dist[i][j]) {
                    dist[i][j] = through;
                    path[i][j] = path[k][j]; // อัปเดต predecessor
                }
            }
        }
    }
}

// ------------------------------------
// main()
// ------------------------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));
    vector<vector<int>> path(n + 1, vector<int>(n + 1, -1));

    // ค่าเริ่มต้น
    for (int i = 1; i <= n; i++) {
        dist[i][i] = 0;
        path[i][i] = -1; // ตัวเองไม่ต้องมี predecessor
    }

    // อ่านกราฟ
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (w < dist[u][v]) {
            dist[u][v] = w;
            dist[v][u] = w;
            path[u][v] = u;
            path[v][u] = v;
        }
    }

    // ก่อนเริ่ม
    printMatrix(dist, n, "D(0) – เริ่มต้น");
    printMatrix(path, n, "π(0) – เริ่มต้น");

    // คำนวณ Floyd–Warshall
    floydMinMax(dist, path, n);

    // หลังจบทั้งหมด
    printMatrix(dist, n, "D(7) – ตารางเสียงดังที่สุดน้อยที่สุด");
    printMatrix(path, n, "π(7) – ตาราง Predecessor ที่ถูกต้อง");

    // ตอบคำถาม
    cout << "\n=== คำตอบ ===\n";
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        if (dist[a][b] == INF) {
            cout << "ไม่มีเส้นทางจาก " << a << " → " << b << "\n";
        } else {
            cout << "\nเสียงดังที่สุดน้อยที่สุดจาก " << a << " → " << b 
                 << " = " << dist[a][b] << "\n";

            vector<int> route = reconstructPath(a, b, path);
            cout << "เส้นทาง: ";
            for (size_t j = 0; j < route.size(); j++) {
                cout << route[j];
                if (j + 1 < route.size()) cout << " → ";
            }
            cout << "\n";
        }
    }

    return 0;
}