#include <stdio.h>
#include <math.h>

int FindGCD1(int m, int n) {
    int gcd = 1;
    for (int i = 2; i <= m && i <= n; i++) {
        while (m % i == 0 && n % i == 0) {
            gcd *= i;
            m /= i;
            n /= i;
        }
    }
    return gcd;
}

int FindGCD2(int m, int n) {
    int max_val;
    if (m > n) max_val = m;
    else max_val = n;

    int limit = (int)sqrt(max_val) + 1;
    int isPrime[limit+1];
    for (int i = 0; i <= limit; i++) isPrime[i] = 1;
    isPrime[0] = isPrime[1] = 0;

    for (int i = 2; i * i <= limit; i++)
        if (isPrime[i])
            for (int j = i * i; j <= limit; j += i)
                isPrime[j] = 0;

    int gcd = 1;
    for (int p = 2; p <= limit; p++)
        if (isPrime[p])
            while (m % p == 0 && n % p == 0) {
                gcd *= p;
                m /= p;
                n /= p;
            }

    if (m > 1 && n > 1) {
        if (m == n) {
            gcd *= m;
        } else {
            int temp_m = m, temp_n = n;
            while (temp_n != 0) {
                int temp = temp_n;
                temp_n = temp_m % temp_n;
                temp_m = temp;
            }
            gcd *= temp_m;
        }
    }

    return gcd;
}

int FindGCD3(int m, int n) {
    while (n != 0) {
        int temp = n;
        n = m % n;
        m = temp;
    }
    return m;
}

int main() {
    int m, n;
    printf("Enter m: ");
    scanf("%d", &m);
    printf("Enter n: ");
    scanf("%d", &n);
    if (m <= 0 || n <= 0) {
        printf("Please enter positive integers only.");
        return 1;
    }

    printf("FindGCD1 = %d\n", FindGCD1(m, n));
    printf("FindGCD2 = %d\n", FindGCD2(m, n));
    printf("FindGCD3 = %d\n", FindGCD3(m, n));

    return 0;
}
