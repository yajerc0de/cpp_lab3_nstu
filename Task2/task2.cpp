#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef unsigned int ui;

// -------- модульное возведение --------
ui mod_pow(ui a, ui e, ui mod) {
    ui res = 1;
    a %= mod;

    while (e > 0) {
        if (e & 1)
            res = (ui)((res * a) % mod);

        a = (ui)((a * a) % mod);
        e >>= 1;
    }

    return res;
}

// -------- решето --------
vector<int> sieve(int n = 500) {
    vector<bool> isPrime(n + 1, true);
    vector<int> primes;

    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (int j = i * 2; j <= n; j += i)
                isPrime[j] = false;
        }
    }

    return primes;
}

// -------- Диемитко --------
bool diemitko(ui p, ui q) {
    ui a = 2;

    if (mod_pow(a, p - 1, p) != 1)
        return false;

    ui exp = (p - 1) / q;

    if (mod_pow(a, exp, p) == 1)
        return false;

    return true;
}

// -------- выбор q --------
ui get_q(vector<int>& primes, int bits) {
    int need = (bits + 1) / 2;

    for (int p : primes) {
        int b = (int)log2(p) + 1;
        if (b == need)
            return (ui)p;
    }

    return 11;
}

// -------- генерация кандидата --------
ui generate_candidate(int bits, ui q, ui u) {

    double xi = (double)rand() / RAND_MAX;

    ui two_t_1 = 1u << (bits - 1);

    ui N = (two_t_1 / q) +
           (ui)((two_t_1 * xi) / q);

    if (N % 2 == 1)
        N++;

    return (N + u) * q + 1;
}

int main() {
    srand(time(0));

    int bits;
    cin >> bits;

    vector<int> primes = sieve();
    ui q = get_q(primes, bits);

    ui limit = 1u << bits;

    cout << "q = " << q << "\n\n";

    for (int i = 1; i <= 10; i++) {

        ui p;
        ui u = 0;
        bool found = false;

        for (int attempt = 0; attempt < 300; attempt++) {

            p = generate_candidate(bits, q, u);
            u += 2;

            if (p > limit)
                continue;

            if (diemitko(p, q)) {
                found = true;
                break;
            }
        }

        if (found)
            cout << i << ") p = " << p << endl;
        else
            cout << i << ") FAILED" << endl;
    }

    return 0;
}