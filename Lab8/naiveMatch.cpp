#include <bits/stdc++.h>
using namespace std;

// ---------- Compute prefix π ----------
vector<int> computeLPS(const string &pat) {
    int m = pat.size();
    vector<int> lps(m, 0);
    int len = 0;
    for (int i = 1; i < m; ) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0)
                len = lps[len - 1];
            else
                lps[i++] = 0;
        }
    }
    return lps;
}

// ---------- KMP search ----------
vector<int> kmpSearchLR(const string &txt, const string &pat) {
    vector<int> res;
    int n = txt.size(), m = pat.size();
    vector<int> lps = computeLPS(pat);
    int i = 0, j = 0;
    while (i < n) {
        if (txt[i] == pat[j]) {
            i++; j++;
            if (j == m) {
                res.push_back(i - m);
                j = lps[j - 1];
            }
        } else if (j != 0)
            j = lps[j - 1];
        else
            i++;
    }
    return res;
}

// ---------- Naïve search ----------
vector<int> naiveSearchLR(const string &txt, const string &pat) {
    vector<int> res;
    int n = txt.size(), m = pat.size();
    for (int s = 0; s <= n - m; s++) {
        bool ok = true;
        for (int k = 0; k < m; k++) {
            if (txt[s + k] != pat[k]) { ok = false; break; }
        }
        if (ok) res.push_back(s);
    }
    return res;
}

// ---------- Remove all whitespace ----------
string stripSpaces(const string &s) {
    string out;
    for (char c : s)
        if (!isspace(static_cast<unsigned char>(c)))
            out += c;
    return out;
}

// ---------- Build & print result ----------
void printResult(const string &title, const vector<int> &lps, const vector<pair<int,string>> &matches) {
    cout << "=== " << title << " ===\n";
    // Prefix π
    for (int i = 0; i < (int)lps.size(); i++) {
        cout << lps[i];
        if (i != (int)lps.size() - 1) cout << " ";
    }
    cout << "\n";

    // จำนวนคำตอบ
    cout << matches.size() << "\n";

    // ตำแหน่ง + ทิศทาง
    for (int i = 0; i < (int)matches.size(); i++) {
        cout << matches[i].first << " " << matches[i].second;
        if (i != (int)matches.size() - 1) cout << "\n";
    }
    cout << "\n";
}

// ---------- Process & build match list ----------
vector<pair<int,string>> buildMatches(const vector<int> &lr, const vector<int> &rl, int plen) {
    vector<pair<int,string>> matches;
    for (int s : lr)
        matches.push_back({s + 1, "LR"});       // เริ่มต้น (1-based)
    for (int s : rl)
        matches.push_back({s + plen, "RL"});    // ปลายขวา (1-based)
    sort(matches.begin(), matches.end(),
         [](auto &a, auto &b){
             return a.first == b.first ? a.second < b.second : a.first < b.first;
         });
    return matches;
}

// ---------- Main ----------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string alphabet;
    getline(cin, alphabet);
    int m, n;
    cin >> m >> n;
    cin.ignore();

    string patternLine, textLine;
    getline(cin, patternLine);
    getline(cin, textLine);

    string pattern = stripSpaces(patternLine);
    string text    = stripSpaces(textLine);

    // prefix table (ใช้ร่วมกัน)
    vector<int> lps = computeLPS(pattern);

    // -------- KMP --------
    vector<int> lr_kmp = kmpSearchLR(text, pattern);
    string revPat = pattern; reverse(revPat.begin(), revPat.end());
    vector<int> rl_kmp = kmpSearchLR(text, revPat);
    auto matchesKMP = buildMatches(lr_kmp, rl_kmp, pattern.size());

    // -------- Naïve --------
    vector<int> lr_naive = naiveSearchLR(text, pattern);
    vector<int> rl_naive = naiveSearchLR(text, revPat);
    auto matchesNaive = buildMatches(lr_naive, rl_naive, pattern.size());

    // -------- Output --------
    printResult("KMP Algorithm", lps, matchesKMP);
    printResult("Naive Algorithm", lps, matchesNaive);

    return 0;
}
