#include <stdio.h>
#include <math.h>

int FindGCD1(int m, int n) {
     printf("Naive solution\n");
    int orig_m = m, orig_n = n;
    int gcd = 1;
    
    printf("m = %d, n = %d\n", orig_m, orig_n);
    
    printf("Prime factors of %d: ", orig_m);
    int temp_m = orig_m;
    for (int i = 2; i <= temp_m; i++) {
        while (temp_m % i == 0) {
            printf("%d ", i);
            temp_m /= i;
        }
    }
    printf("\n");

    printf("Prime factors of %d: ", orig_n);
    int temp_n = orig_n;
    for (int i = 2; i <= temp_n; i++) {
        while (temp_n % i == 0) {
            printf("%d ", i);
            temp_n /= i;
        }
    }
    printf("\n");

    printf("Common prime factors: ");
    for (int i = 2; i <= m && i <= n; i++) {
        while (m % i == 0 && n % i == 0) {
            printf("%d ", i);
            gcd *= i;
            m /= i;
            n /= i;
        }
    }
    
    printf("\nGCD = product of common factors = %d\n", gcd);
    return gcd;
}

int FindGCD2(int m, int n) {
    printf("Sieve of Eratosthenes\n");
    int orig_m = m, orig_n = n;
    int max_val;
    if (m > n) max_val = m;
    else max_val = n;
    
    printf("m = %d, n = %d\n", orig_m, orig_n);
    
    int limit = (int)sqrt(max_val) + 1;
    int isPrime[limit+1];
    
    for (int i = 0; i <= limit; i++) {
        isPrime[i] = 1;
    }
    isPrime[0] = isPrime[1] = 0;
    
    for (int i = 2; i * i <= limit; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                isPrime[j] = 0;
            }
        }
    }
    
    printf("Prime factors of %d: ", orig_m);
    int temp_m = orig_m;
    for (int i = 2; i <= temp_m; i++) {
        while (temp_m % i == 0) {
            printf("%d ", i);
            temp_m /= i;
        }
    }
    printf("\n");
    
    printf("Prime factors of %d: ", orig_n);
    int temp_n = orig_n;
    for (int i = 2; i <= temp_n; i++) {
        while (temp_n % i == 0) {
            printf("%d ", i);
            temp_n /= i;
        }
    }
    printf("\n");
    
    printf("Common prime factors: ");
    int gcd = 1;
    

    for (int p = 2; p <= limit; p++) {
        if (isPrime[p]) {
            while (m % p == 0 && n % p == 0) {
                printf("%d ", p);
                gcd *= p;
                m /= p;
                n /= p;
            }
        }
    }
    

    if (m > 1 && n > 1) {
        if (m == n) {
            printf("%d ", m);
            gcd *= m;
        } else {
            int temp_m = m, temp_n = n;
            while (temp_n != 0) {
                int temp = temp_n;
                temp_n = temp_m % temp_n;
                temp_m = temp;
            }
            if (temp_m > 1) {
                printf("%d ", temp_m);
                gcd *= temp_m;
            }
        }
    }
    
    printf("\nGCD = product of common factors = %d\n", gcd);
    return gcd;
}

int FindGCD3(int m, int n) {
    printf("Euclidean Algorithm\n");
    while (n != 0) {
        int temp = n;
        n = m % n;
        m = temp;
    }
    
    printf("GCD = %d\n", m);
    return m;
}

int main() {
    int m, n;
    printf("Enter m: ");
    scanf("%d", &m);
    printf("Enter n: ");
    scanf("%d", &n);
    
    if (m <= 0 || n <= 0) {
        printf("Please enter positive integers only.\n");
        return 1;
    }
    
    int result1 = FindGCD1(m, n);
    int result2 = FindGCD2(m, n);
    int result3 = FindGCD3(m, n);
    
    printf("FindGCD1 = %d\n", result1);
    printf("FindGCD2 = %d\n", result2);
    printf("FindGCD3 = %d\n", result3);
    
    return 0;
}