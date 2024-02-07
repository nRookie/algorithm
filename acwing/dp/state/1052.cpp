#include<iostream>
using namespace std;

const int N = 1e6 + 10;

int dp[N][2][2];
int a[N];

int main() {
    int n, k;
    cin >> n ;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    dp[1][1][0] = -a[1];
    for (int i = 2; i <= n; i ++) {
        
        // 卖出
        dp[i][0][0] = max(dp[i - 1][0][0], dp[i - 1][1][0] + a[i] );
        // 买入股票 , i, 1, 0 // 0表示刚买入，
        dp[i][0][1] = max(dp[i - 1][0][0], dp[i - 1][0][1]);

        dp[i][1][0] = max(dp[i - 1][1][0] ,dp[i - 1][0][1] - a[i]);
        // 1表示买入后超过1天了
    }

    cout << max(dp[n][0][0], dp[n][0][1]) << endl;
    
    
}