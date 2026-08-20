#include <bits/stdc++.h>
using namespace std;

// parse "{1,2,2}" -> vector<int>{1,2,2}
vector<int> parseInput(const string& s) {
    vector<int> result;
    string num;
    for (char c : s) {
        if (isdigit(c) || c=='-' ) num += c;
        else if (c==',' || c=='}') {
            if (!num.empty()) { result.push_back(stoi(num)); num.clear(); }
        }
    }
    if (!num.empty()) result.push_back(stoi(num));
    return result;
}

// เก็บผลลัพธ์ทั้งหมด (กันซ้ำ)
set<string> allSets;

// สร้างสตริงของเซตจากรายการ (value, isWrapped)
string buildSetString(vector<pair<int,bool>> items) {
    // จัดเรียงแบบ canonical: ค่าน้อยมาก่อน, ถ้าเท่ากัน ให้ตัวเลข (ไม่ wrap) มาก่อน {x}
    sort(items.begin(), items.end(), [](auto& a, auto& b){
        if (a.first != b.first) return a.first < b.first;
        return a.second < b.second; // false(0)=ไม่ห่อ มาก่อน true(1)=ห่อ
    });
    string out = "{";
    for (int i = 0; i < (int)items.size(); ++i) {
        if (items[i].second) out += "{" + to_string(items[i].first) + "}";
        else out += to_string(items[i].first);
        if (i + 1 < (int)items.size()) out += ",";
    }
    out += "}";
    return out;
}

// กระจายจำนวน wrap สำหรับแต่ละค่าที่เลือกมา
void emitWraps(
    const vector<pair<int,int>>& uniq,           // (value, frequency in input)
    const vector<int>& take,                     // เลือกค่าละกี่ตัว
    int idx,
    vector<int>& wrap                            // เลือกห่อกี่ตัวของค่านั้น
){
    if (idx == (int)uniq.size()) {
        // สร้างรายการ (value, isWrapped) ตาม take และ wrap
        vector<pair<int,bool>> items;
        for (int i = 0; i < (int)uniq.size(); ++i) {
            int val = uniq[i].first;
            int cnt = take[i];
            int w   = wrap[i];
            int plain = cnt - w;
            // ใส่ตัวเลขปกติ
            for (int k = 0; k < plain; ++k) items.push_back({val,false});
            // ใส่ตัวที่ห่อเป็น {val}
            for (int k = 0; k < w; ++k) items.push_back({val,true});
        }
        allSets.insert(buildSetString(items));
        return;
    }

    int cnt = take[idx];
    int maxWrap = 0;
    // อนุญาตให้ wrap ได้เฉพาะกรณีเลือกค่าตัวนี้ >= 2
    // และไม่ให้ "wrap ทั้งหมด" เพื่อเลี่ยง {{2},{2}} ที่มักไม่ต้องการ
    if (cnt >= 2) maxWrap = cnt - 1; // 0..cnt-1
    for (int w = 0; w <= maxWrap; ++w) {
        wrap[idx] = w;
        emitWraps(uniq, take, idx + 1, wrap);
    }
}

// ไล่จำนวนที่จะเลือกของแต่ละค่า (0..freq)
void chooseCounts(
    const vector<pair<int,int>>& uniq, // (value, total frequency)
    int idx,
    vector<int>& take
){
    if (idx == (int)uniq.size()) {
        // กรณีว่างเปล่า {} ก็จะถูกสร้างด้วย wrap รวมด้วย
        vector<int> wrap(uniq.size(), 0);
        emitWraps(uniq, take, 0, wrap);
        return;
    }
    int freq = uniq[idx].second;
    for (int c = 0; c <= freq; ++c) {
        take[idx] = c;
        chooseCounts(uniq, idx + 1, take);
    }
}

void generateSetsWithOptionalSingletonWraps(vector<int> a) {
    sort(a.begin(), a.end());
    // อัดให้เหลือ (value, freq)
    vector<pair<int,int>> uniq;
    for (int x : a) {
        if (uniq.empty() || uniq.back().first != x) uniq.push_back({x,1});
        else uniq.back().second++;
    }
    vector<int> take(uniq.size(), 0);
    chooseCounts(uniq, 0, take);

    // แสดงผลเรียงตาม lexicographic ของสตริง (ดูง่ายและไม่ซ้ำ)
    for (auto& s : allSets) cout << s << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "Enter set : ";
    string input; 
    cin >> input;

    vector<int> T = parseInput(input);
    generateSetsWithOptionalSingletonWraps(T);
    return 0;
}
