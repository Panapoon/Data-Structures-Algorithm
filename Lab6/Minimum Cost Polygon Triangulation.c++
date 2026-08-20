#include <bits/stdc++.h>
using namespace std;

// ------------------- ฟังก์ชันพื้นฐาน -------------------
double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

double tri(vector<double>& x, vector<double>& y, int i, int k, int j) {
    return dist(x[i], y[i], x[k], y[k])
         + dist(x[k], y[k], x[j], y[j])
         + dist(x[j], y[j], x[i], y[i]);
}

// ------------------- บรูทฟอร์ซ (Recursive) -------------------
double bruteForce(vector<double>& x, vector<double>& y, int i, int j) {
    if (j < i + 2) return 0; // น้อยกว่า 3 จุด ไม่มีสามเหลี่ยม
    double ans = 1e300;
    for (int k = i + 1; k < j; ++k) {
        double cost = bruteForce(x, y, i, k)
                    + bruteForce(x, y, k, j)
                    + tri(x, y, i, k, j);
        ans = min(ans, cost);
    }
    return ans;
}

// ------------------- โปรแกรมหลัก -------------------
int main() {
    int n;
    cin >> n;
    vector<double> x(n), y(n);
    for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];

    const double INF = 1e300;
    vector<vector<double>> dp(n, vector<double>(n, 0.0));

    // ---------- DP Bottom-Up ----------
    for (int gap = 2; gap < n; ++gap) {
        for (int i = 0; i + gap < n; ++i) {
            int j = i + gap;
            double best = INF;
            for (int k = i + 1; k < j; ++k)
                best = min(best, dp[i][k] + dp[k][j] + tri(x, y, i, k, j));
            dp[i][j] = best;
        }
    }

    // ---------- แสดงตาราง DP ----------
    cout << fixed << setprecision(4);
    cout << "DP Table\n";
    cout << "--------------------------------------------\n";
    cout << setw(6) << "i/j";
    for (int j = 0; j < n; ++j) cout << setw(12) << j;
    cout << "\n--------------------------------------------\n";

    for (int i = 0; i < n; ++i) {
        cout << setw(6) << i;
        for (int j = 0; j < n; ++j) {
            if (j < i) cout << setw(12) << "-";
            else if (j == i || j == i + 1) cout << setw(12) << "0";
            else cout << setw(12) << dp[i][j];
        }
        cout << "\n";
    }

    // ---------- ใช้ข้อมูลจากตาราง ----------
    cout << "\nMinimum total perimeter (DP) = " << dp[0][n - 1] << "\n";

    // ---------- เรียกใช้บรูทฟอร์ซ ----------
    double bruteAns = bruteForce(x, y, 0, n - 1);
    cout << "Minimum total perimeter (Brute Force) = " << bruteAns << "\n";

    return 0;
}
