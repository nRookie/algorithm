#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 2e5+5;
long long dp[MAXN][505]; // Assuming K <= 500
pair<int, int> balls[MAXN];

int main() {
    int N, K;
    cin >> N >> K;
    for(int i = 0; i < N; ++i) {
        cin >> balls[i].first >> balls[i].second; // Color, Value
    }

    // Initialize DP array
    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <= K; ++j) {
            dp[i][j] = -1;
        }
    }
    dp[0][0] = 0;

    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j <= K; ++j) {
            // Case 1: Skip the current ball (if j > 0)
            if (j > 0 && dp[i-1][j-1] != -1) {
                dp[i][j] = max(dp[i][j], dp[i-1][j-1]);
            }
            // Case 2: Take the current ball
            if (dp[i-1][j] != -1) {
                dp[i][j] = max(dp[i][j], dp[i-1][j] + balls[i-1].second);
            }
        }
    }

    // Find the answer
    long long ans = -1;
    for (int j = 0; j <= K; ++j) {
        if (dp[N][j] != -1) {
            ans = max(ans, dp[N][j]);
        }
    }

    cout << ans << endl;

    return 0;
}
