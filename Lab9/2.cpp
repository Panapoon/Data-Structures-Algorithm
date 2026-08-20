#include <iostream>    // cin, cout
#include <vector>      // vector<>
#include <string>      // string
#include <algorithm>   // sort(), find(), ฯลฯ
#include <iomanip>     // setw, setprecision
using namespace std;

enum Color { WHITE, GRAY, BLACK };

// ฟังก์ชันแสดงชื่อสี (เอาไว้พิมพ์ผล)
string colorName(Color c) {
    if (c == WHITE) return "WHITE";
    if (c == GRAY)  return "GRAY";
    return "BLACK";
}

// --------------------------------------
// DFS visit (พร้อมโชว์การเปลี่ยนสี)
// --------------------------------------
void dfs_visit(int u, const vector<vector<int>>& adj, vector<Color>& color) {
    color[u] = GRAY;
    cout << "Discover " << u << " (turns GRAY)\n";

    for (int v : adj[u]) {
        if (color[v] == WHITE) {
            cout << "  " << u << " → " << v << " (tree edge)\n";
            dfs_visit(v, adj, color);
        }
    }

    color[u] = BLACK;
    cout << "Finish " << u << " (turns BLACK)\n";
}

// --------------------------------------
// DFS ตรวจว่าทุกเมืองโดนเยี่ยมหรือไม่
// --------------------------------------
bool dfs_check_all(const vector<vector<int>>& adj, int N) {
    vector<Color> color(N + 1, WHITE);

    cout << "\nInitial colors: ";
    for (int i = 1; i <= N; i++) cout << i << ":" << colorName(color[i]) << " ";
    cout << "\n";

    dfs_visit(1, adj, color);

    cout << "\nFinal colors:   ";
    for (int i = 1; i <= N; i++) cout << i << ":" << colorName(color[i]) << " ";
    cout << "\n";

    // ตรวจว่ามี WHITE เหลือไหม
    for (int i = 1; i <= N; i++) {
        if (color[i] == WHITE) {
            cout << "Node " << i << " still WHITE → not reachable.\n";
            return false;
        }
    }
    return true;
}

// --------------------------------------
// ตรวจ Strongly Connected (2 รอบ)
// --------------------------------------
bool isStronglyConnected(int N, const vector<vector<int>>& adj) {
    cout << "\n========== Round 1: Normal Graph ==========\n";
    if (!dfs_check_all(adj, N))
        return false;

    // สร้างกราฟกลับทิศ
    vector<vector<int>> rev(N + 1);
    for (int u = 1; u <= N; u++)
        for (int v : adj[u])
            rev[v].push_back(u);

    cout << "\n========== Round 2: Reversed Graph ==========\n";
    if (!dfs_check_all(rev, N))
        return false;

    return true;
}

// --------------------------------------
// main()
// --------------------------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    while (cin >> N >> M) {
        if (N == 0 && M == 0) break;

        vector<vector<int>> adj(N + 1);

        for (int i = 0; i < M; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            if (c == 1)
                adj[a].push_back(b);      // ทางเดียว
            else if (c == 2) {
                adj[a].push_back(b);
                adj[b].push_back(a);      // สองทาง
            }
        }

        cout << "\n============================================\n";
        cout << "Graph check: N=" << N << ", M=" << M << "\n";

        bool result = isStronglyConnected(N, adj);
        cout << "\nResult → " << (result ? 1 : 0) << "\n";
        cout << "============================================\n";
    }
    return 0;
}
