#include <iostream>
#include <vector>
using namespace std;

int bestMove(vector<int>& a, int pos, int n, int m, int lastTake) {
    int limit = min(m, n - pos);

    int bestSum = -2000000000;
    int bestK = 1;
    int curSum = 0;

    for (int k = 1; k <= limit; k++) {
        curSum += a[pos + k - 1];

        if (k == lastTake) continue;

        if (curSum > bestSum || (curSum == bestSum && k < bestK)) {
            bestSum = curSum;
            bestK = k;
        }
    }

    return bestK;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int pavel = 0, vika = 0;
    int lastPavel = 0, lastVika = 0;

    int pos = 0;
    int turn = 0;

    while (pos < n) {
        int take;

        if (turn == 0)
            take = bestMove(a, pos, n, m, lastPavel);
        else
            take = bestMove(a, pos, n, m, lastVika);

        int sum = 0;
        for (int i = 0; i < take; i++)
            sum += a[pos + i];

        if (turn == 0) {
            pavel += sum;
            lastPavel = take;
        } else {
            vika += sum;
            lastVika = take;
        }

        pos += take;
        turn = 1 - turn;
    }

    cout << (pavel > vika ? 1 : 0);
    return 0;
}