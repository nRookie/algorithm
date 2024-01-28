#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

const long long INF = 1 << 30;

const int N = 22;


int main() {
    int n, m;
    cin >> n >> m;
    vector< vector<int>> d(n, vector<int> (n, INF));
    while (m -- ) {
        int a, b, c;
        cin >> a >> b >> c;
        a --;
        b --;
        d[a][b] =  c;
        d[b][a] = c;
    }

    for (int k = 0; k < n; k ++) {
        for (int i = 0; i < n; i ++)
            for (int j = 0; j < n; j ++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    }

    // dp[S][i]: The minimum total weight of the edges traversed for walks that start from any vertex and end at vertex  i, with the set of vertices traversed being 
    // S.
    // dp[i][j] vist the vertex in is and the last visited vertex is j 
    vector< vector<int>> dp(1 << n, vector<int> (n, INF));

    for (int i = 0; i < n; i ++) dp[1 << i][i] = 0;

    for (int bit = 0; bit < 1 << n; bit ++) {
        for (int i = 0; i < n; i ++) {
            if(~bit >> i & 1) continue;
            if(dp[bit][i] == INF) continue;
            for (int j = 0; j < n; j ++) {
                if(bit & (1 << j) ) continue;
                if (d[i][j] == INF) continue;
                dp[bit | 1 << j][j] = min(  dp[bit | 1 << j][j] , dp[bit][i] + d[i][j]);
            }
        }
    }
    int ans = INF ;

    for (int i = 0; i < n; i ++) {
        ans = min(ans, dp [ (1 << n)  - 1][i] );
    }

    cout << ans << endl;

    return 0;
}
