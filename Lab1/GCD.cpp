#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;

long long int ops = 0; // global counter

// นับจำนวนหลักของเลข
long long int countDigits(long long int x) {
    long long int cnt = 0;
    if (x == 0) return 1;
    while (x > 0) {
        cnt++;
        x /= 10;
    }
    return cnt;
}

// ============= Prime Factorization แบบไม่ใช้ sieve =============
vector<long long int> prime_fact(long long int x) {
    vector<long long int> prime_factorization;
    long long int x_max = x;
    long long int i = 2;
    while (i <= x_max) { ops++;
        if (x % i == 0) { ops++;
            prime_factorization.push_back(i); ops++;
            x = x / i; ops++;
        }
        else { i += 1; ops++; }
    }
    return prime_factorization;
}

// ============= Prime Factorization แบบ sieve =============
vector<long long int> prime_fact_sieve(long long int x) {
    vector<long long int> final_result;

    // Step 1: สร้าง sieve [0..x]
    vector<bool> isPrime(x + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (long long int i = 2; i * i <= x; i++) {
        if (isPrime[i]) {
            for (long long int j = i * i; j <= x; j += i) {
                isPrime[j] = false;
            }
        }
    }

    // Step 2: factorize
    for (long long int i = 2; i <= x; i++) {
        if (isPrime[i]) {
            long long int x_copy = x;
            while (x_copy % i == 0) {
                final_result.push_back(i); ops++;
                x_copy /= i; ops++;
            }
        }
    }

    return final_result;
}

// ============= หา common prime factors =============
vector<long long int> common_prime(vector<long long int> m, vector<long long int> n) {
    vector<long long int> result;
    long long int m_index = 0;
    long long int n_index = 0;
    while (true) { ops++;
        if (m_index > (long long int)m.size() - 1 || n_index > (long long int)n.size() - 1) return result;
        if (m[m_index] == n[n_index]) { ops++;
            result.push_back(m[m_index]); ops++;
            m_index++; ops++;
            n_index++; ops++;
        }
        else if (m[m_index] < n[n_index]) { ops++;
            m_index++; ops++;
        }
        else if (m[m_index] > n[n_index]) { ops++;
            n_index++; ops++;
        }
    }
    return result;
}

// ============= คูณผลลัพธ์กลับเป็นค่า GCD =============
long long int multiple(vector<long long int> input) {
    if (input.size() == 0) return 0;
    long long int result = 1;
    for (long long int iter : input) { ops++;
        result = result * iter; ops++;
    }
    return result;
}

// ============= Check input < 2 =============
bool check_below_2(long long int m, long long int n) {
    if (m < 2 && n < 2) { ops++;
        cout << "No Prime Factor\n";
        return true;
    }
    else if (m < 2) { ops++;
        cout << "m No Prime Factor\n";
        return true;
    }
    else if (n < 2) { ops++;
        cout << "n No Prime Factor\n";
        return true;
    }
    return false;
}

// ============= GCD Methods =============
long long int FindGCD1(long long int m, long long int n) {
    if (check_below_2(m,n)) return 0;
    vector<long long int> m_prime = prime_fact(m);
    vector<long long int> n_prime = prime_fact(n);
    vector<long long int> common_prime_val = common_prime(m_prime, n_prime);
    return multiple(common_prime_val);
}

long long int FindGCD2(long long int m, long long int n) {
    if (check_below_2(m,n)) return 0;
    vector<long long int> m_prime = prime_fact_sieve(m);
    vector<long long int> n_prime = prime_fact_sieve(n);
    vector<long long int> common_prime_val = common_prime(m_prime, n_prime);
    return multiple(common_prime_val);
}

// ============= MAIN =============
int main() {
    ifstream file("Extra Case2 plot.txt");
    if (!file) {
        cerr << "ไม่สามารถเปิดไฟล์ Extra Case2 plot.txt ได้\n";
        return 1;
    }

    //ofstream out1("ops_GCD1.csv");
    ofstream out2("ops_GCD2.csv");

    //out1 << "dataset_index,digits,operations\n";
    out2 << "dataset_index,digits,operations\n";

    long long int m, n;
    long long int index = 1;

    while (file >> m) {
        if (file.peek() == ',') file.ignore();
        file >> n;

        cout << "read: " << m << " , " << n << endl;

        long long int digits = max(countDigits(m), countDigits(n));

        // FindGCD1
        //ops = 0;
        //FindGCD1(m, n);
        //long long int ops1 = ops;

        // FindGCD2
        ops = 0;
        FindGCD2(m, n);
        long long int ops2 = ops;

        //out1 << index << "," << digits << "," << ops1 << "\n";
        out2 << index << "," << digits << "," << ops2 << "\n";

        index++;
    }

    file.close();
    //out1.close();
    out2.close();

    cout << "สร้างไฟล์ ops_GCD1.csv และ ops_GCD2.csv เรียบร้อย\n";
    return 0;
}
