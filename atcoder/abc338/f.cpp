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

    for (int i = 0; i < n; i++) d[i][i] = 0;
    while (m -- ) {
        int a, b, c;
        cin >> a >> b >> c;
        a --;
        b --;
        d[a][b] =  c;
        // d[b][a] = c; // directed graph
    }

    for (int k = 0; k < n; k ++) 
        for (int i = 0; i < n; i ++)
            for (int j = 0; j < n; j ++) {
                if (d[i][k] == INF or d[k][j] == INF) continue; 
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }

    // dp[S][i]: The minimum total weight of the edges traversed for walks that start from any vertex and end at vertex  i, with the set of vertices traversed being 
    // S.
    // dp[i][j] vist the vertex in is and the last visited vertex is j 
    vector< vector<int>> dp(1 << n, vector<int> (n, INF));

    for (int i = 0; i < n; i ++) dp[1 << i][i] = 0;

    for (int bit = 0; bit < (1 << n) -1; bit ++) {
        for (int i = 0; i < n; i ++) {
            if(~bit >> i & 1) continue;
            if(dp[bit][i] == INF) continue;
            for (int j = 0; j < n; j ++) {
                if(bit >> j & 1)  continue;
                if (d[i][j] == INF) continue;
                dp[bit | 1 << j][j] = min(  dp[bit | 1 << j][j] , dp[bit][i] + d[i][j]);
            }
        }
    }
    int ans = INF ;

    for (int i = 0; i < n; i ++) {
        ans = min(ans, dp [ (1 << n)  - 1][i] );
    }
    if (ans == INF) cout << "No" << endl;
    cout << ans << endl;

    return 0;
}
