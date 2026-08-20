#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> contain_change;

void find_change(int amount, vector<int> change, vector<int> coins, int start){
    if (amount == 0){
        contain_change.push_back(change);
        return;
    }
    else if (amount < 0) return;
    else {
        for (int i = start; i < coins.size();i++){
            vector<int> next_change = change;
            next_change.push_back(coins[i]);
            int next_amount = amount - coins[i];
            find_change(next_amount, next_change, coins, i);
        }
        return;
    }
}
void show_info(string Amount, string Coins) {
    vector<int> change;
    string num = "";
    int amount = stoi(Amount);
    vector<int> coins;

    for (char c : Coins) {
        if (c == ' ') {
            if (!num.empty()) {
                coins.push_back(stoi(num));
                num = "";
            }
        } else {
            num += c;
        }
    }
    if (!num.empty()) {
        coins.push_back(stoi(num));
    }

    find_change(amount, change, coins,0);

    cout << "Amount = " << amount << endl;
    cout << "Ways:" << contain_change.size() << endl;
    for (auto &comb : contain_change) {
        cout << "{ ";
        for (int c : comb) cout << c << " ";
        cout << "}" << endl;
    }
}

int main(){
    string Amount, Coins;
    cout << "Amount: ";
    cin >> Amount;
    cin.ignore();
    cout << "Coins: ";
    getline(cin, Coins);
    show_info(Amount, Coins);
}