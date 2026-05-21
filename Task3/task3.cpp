#include <iostream>
#include <vector>

using namespace std;

int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    int a, b;
    cin >> a >> b;

    if (b == 1) {
        cout << "infinity";
        return 0;
    }

    vector<vector<int>> S(a + 1, vector<int>(a + 1, 0));
    S[0][0] = 1;

    for (int n = 1; n <= a; n++) {
        for (int k = 1; k <= n; k++) {
            S[n][k] = S[n - 1][k - 1] + k * S[n - 1][k];
        }
    }

    vector<int> fact(a + 1, 1);
    for (int i = 1; i <= a; i++) {
        fact[i] = fact[i - 1] * i;
    }

    int num = 0;

    for (int k = 1; k <= a; k++) {
        int term = S[a][k] * fact[k] * b;

        int pw = 1;
        for (int i = 0; i < a - k; i++) {
            pw *= (b - 1);
        }

        term *= pw;
        num += term;
    }

    int den = 1;
    for (int i = 0; i < a + 1; i++) {
        den *= (b - 1);
    }

    int g = gcd(num, den);

    cout << num / g << "/" << den / g;

    return 0;
}