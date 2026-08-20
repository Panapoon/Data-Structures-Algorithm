#include <bits/stdc++.h>
using namespace std;

vector<vector<vector<vector<int>>>> waysTable;
vector<vector<int>> countTable;

void showInfo(string Amount, string Coins){
    waysTable.clear();
    countTable.clear();

    vector<int> change;
    int amount = stoi(Amount);
    vector<int> coins;

    vector<vector<vector<int>>> columnVector(amount+1,vector<vector<int>>());
    columnVector[0].push_back(vector<int>());
    waysTable.push_back(columnVector);

    vector<int> countColumn(amount+1, 0);
    countColumn[0] = 1; 
    countTable.push_back(countColumn);

    stringstream ss(Coins);
    int coin;
    while (ss >> coin) {
        coins.push_back(coin);
        waysTable.push_back(columnVector);
        countTable.push_back(countColumn);
    }

    stable_sort(coins.begin(),coins.end());

 
    for (int row = 1; row <= coins.size(); row++){
        for (int column = 0; column <= amount; column++){
            if (column == 0) {
                countTable[row][column] = 1;
                continue;
            }
            else if (column >= coins[row-1]){
                countTable[row][column] = countTable[row][column - coins[row-1]] + countTable[row-1][column];
                for (int i = 0; i < waysTable[row][column-coins[row-1]].size(); i++){
                    vector<int> newVector = waysTable[row][column - coins[row-1]][i];
                    newVector.push_back(coins[row-1]);
                    waysTable[row][column].push_back(newVector);  
                }
                for (int j = 0; j < waysTable[row-1][column].size(); j++){
                    waysTable[row][column].push_back(waysTable[row-1][column][j]);
                }
            }
            else {
                countTable[row][column] =  countTable[row-1][column];
                for (int j = 0; j < waysTable[row-1][column].size(); j++){
                    waysTable[row][column].push_back(waysTable[row-1][column][j]);
                }
            }
        }
    }

    vector<vector<int>> lastVectorVector = waysTable.back().back();

    int minSize = INT_MAX;
    vector<int> minCoins;
    for (auto &comb : lastVectorVector) {
        if ((int)comb.size() < minSize) {
            minSize = comb.size();
            minCoins = comb;
        }
    }
    cout << "Way to make change: " << lastVectorVector.size() << endl;
    cout << "The minimum number of coins is " << minSize << " , which is {";
    for (int i = 0; i < minCoins.size(); i++){
        if (i == minCoins.size()-1){cout << minCoins[i];}
        else {
            cout << minCoins[i] << ",";
        }
    }

    cout << "}" << endl << "All result: " << "" << endl;
    for (vector<int> i : lastVectorVector){
        for (int j : i){
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl << "Table" << endl;
    for (int i = 0;i < countTable[0].size();i++) cout << i << " ";
    cout << endl << string(countTable[0].size() * 2, '-') << endl;
    for(int i = 0;i < countTable.size();i++){
        for(int j = 0; j < countTable[i].size();j++){
            cout << countTable[i][j] << " ";
        }
        cout << endl;
    }    
}

int main(){
    string Amount, Coins;
    cout << "Amount: ";
    cin >> Amount;
    cin.ignore();
    cout << "Coins: ";
    getline(cin, Coins);
    showInfo(Amount, Coins);
}