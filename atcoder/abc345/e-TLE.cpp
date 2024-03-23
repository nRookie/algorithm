#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



// dp[i][j] as maximum value we can get when we have selected elements from [v1,v2, ..., vi] and we have selected elements from [v1v2,...,vi] and we have removed 
// exactly j elements


// dp[0][0] = 0
// dp[0][j] = -inf for 0 < j <= k

// 6th element was removed

// then we should find maximum value when only 2 elements are removed among first 5

//  dp[6][3] = max(dp[6][3], dp[5][2]);

// 6th element was not removed

// then we should find maximum value when 3 elements are removed among first 5 and add current value to it


// dp[6][3] = max(dp[6][3] , v[6] + dp[5][3]);

// how to handle colors ?

// can we add color of last element picked in dp state?

// dp[i][j][c] denotes maximum value we can get when we have removed exactly j elements among first i elements and c is the color of last picked element

// If we do not remove ith element, then for dp[i][j] we should remove j elements 
// from first i - 1 elements, and color of last element is ci

// for col = 1,2, ...., N
// if col != ci
//     dp[i][j][ci] = max(dp[i][j][ci], vi + dp[i - 1][j][col])
// 




// if we do remove ith element

// then for dp[i][j] , we should remove j - 1 elements from first i - 1 elements
// and color of last element remains same

// for col = 1,2, ...., N
//    dp[i][j][col] = max(dp[i][j][col], dp[i - 1][j - 1][col])
// 



int main() {
    int n, k;
    cin >> n >> k;

    vector<int> c(n  +1) , v(n + 1);

    for (int i = 1; i <= n; i ++)
        cin >> c[i] >> v[i];
    
    using ll = long long int;

    const ll inf = 1e15;

    vector<vector<vector<ll>>> dp(n + 1, vector(k + 1, vector(n + 1, -inf)));

    // color 0 is not present in c[1 ... n];
    dp[0][0][0] = 0;

    for (int idx = 1; idx <= n; idx ++) {

        const int currentColor = c[idx], currentValue = v[idx];

        for (int removedCnt = 0; removedCnt <= k; removedCnt ++) {
            for (int pvrColor = 0; pvrColor <= n; ++ pvrColor) {
                if (pvrColor == currentValue)
                    continue;
                dp[idx][removedCnt][currentColor] =
                    max(dp[idx][removedCnt][currentColor], currentValue + dp[idx - 1][removedCnt][pvrColor]);
            }
        }

        // if we remove current element

        for (int removedCnt = 1; removedCnt <= k; removedCnt ++) {
            for (int pvrColor = 0; pvrColor <= n; ++ pvrColor) {
                dp[idx][removedCnt][pvrColor] = 
                    max(dp[idx][removedCnt][pvrColor], 
                        dp[idx - 1][removedCnt - 1][pvrColor]);
            }
        }
    }

    ll ans = -inf;

    for (int pvrColor = 0; pvrColor <= n; pvrColor ++)
        ans = max(ans, dp[n][k][pvrColor]);

    if (ans <0) ans = -1;
    cout << ans << endl;


}