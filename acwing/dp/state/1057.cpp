#include<iostream>
using namespace std;

const int N = 1e6 + 10;

int dp[N][2][110];
int a[N];

int main() {
    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int res = 0;
    
    for (int i = 1; i <= k; i ++) {
        dp[1][1][i] = -a[1];
    }

    for (int i = 2; i <= n; i ++) {

        // dp[i][1][0] = max(dp[i - 1][1][0], dp[i - 1][0][0] - a[i]);
        // dp[i][0][0] = max(dp[i - 1][0][0], dp[i -1][1][0] + a[i] );
        for (int j = 1; j <= k; j ++) {
                dp[i][0][j] = max(dp[i - 1][0][j], dp[i - 1][1][j] + a[i]);
                dp[i][1][j] = max(dp[i - 1][1][j], dp[i - 1][0][j - 1] -a[i]);
            res = max(dp[i][0][j],res);
            // cout << j << " " <<  dp[i][0][j] << " " <<   res << endl;
        }
    }


    std::cout << res << endl;
}