#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;


const int N = 1e6 + 10;
int dp[N][2];
int a[N];
int main() {
    int T;

    cin >> T;

    while (T --) {
        int n; 
        cin >> n;
        memset(dp, 0, sizeof dp);
        // dp[i][0]  not
        // dp[i][1]  stoled

        for (int i = 1; i <= n; i ++) {
            cin >> a[i];
        }
        dp[0][0] = 0;
        dp[0][1] = 0;

        for (int i = 1; i <= n; i ++ ) {
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + a[i]);
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
        }
        cout << max(dp[n][0], dp[n][1]) << endl; 
    }
}