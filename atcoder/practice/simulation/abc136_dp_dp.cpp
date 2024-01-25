// dp =  ”the index of square where children who was initially in square i moves into after j movements.”

// dp[1][j] = j - 1, if ( s[j] =L )
// dp[1][j] = j + 1, if (s[j] = R);

// for any i1, i2, j it holds that dp(i1 + i2, j) = dp(i2, dp(i1, j)), so by using doubling you
// can find dp(X, j)

// dp[i1 + i2][j] = dp[i2][dp[i1, j]]




// RRRLLL
// 111111
#include<iostream>
#include<vector>
#include<map>
using namespace std;


int dp[22][100100];

int main() {
    string s; cin >> s;
    int n = s.size();

    // dp[i][j], on j, moved after 2^i move.
    for (int i = 0; i < n; i ++) {
        if (s[i] == 'R')
        dp[1][i] = (i) + 1;
        else
        dp[1][i] = (i) - 1;

        printf("dp[1][%d]:%d\n", i,  dp[1][i]);
    }

    for (int i = 2; i <= 21; i ++ ) 
        for (int j = 0; j < n; j ++) {
            dp[i][j] = dp[i - 1][dp[i - 1][j]];
            printf("dp[%d][%d] :%d  ", i - 1, j, dp[i - 1][j]);
            printf("dp[%d][%d]:%d\n", i, j,  dp[i][j]);
        }

    map <int, int > mp;

    for (int i = 0; i < n; i ++) {
        int v= dp[21][i];
        mp[v] ++;
    }


    for (int i = 0; i < n; i ++) {
        cout << mp[i] << endl;
    }
}
 