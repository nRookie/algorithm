#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, D;
    cin >> N >> D;
    vector<int> A(N);
    for (int& a : A) {
        cin >> a;
    }

    vector<int> dp(N, 1);
    // dp[i] = maximum length ending with the number i
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            if (abs(A[i] - A[j]) <= D) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    cout << *max_element(dp.begin(), dp.end()) << endl;
    return 0;
}
