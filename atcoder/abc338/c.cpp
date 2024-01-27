#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> Q(N), A(N), B(N);

    for (int i = 0; i < N; ++i) cin >> Q[i];
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < N; ++i) cin >> B[i];

    int maxServings = 0;
    for (int servingsA = 0; servingsA <= 1000000; ++servingsA) {
        bool isFeasible = true;
        int minServingsB = 1000000;

        for (int i = 0; i < N; ++i) {
            if (A[i] > 0 && servingsA > Q[i] / A[i]) {
                isFeasible = false;
                break;
            }
            if (B[i] > 0) {
                minServingsB = min(minServingsB, (Q[i] - A[i] * servingsA) / B[i]);
            }
        }

        if (!isFeasible) break;

        maxServings = max(maxServings, servingsA + minServingsB);
    }

    cout << maxServings << endl;

    return 0;
}
