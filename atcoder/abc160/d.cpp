#include<iostream>
#include<sstream>
#include<cstring>
using namespace std;

const int N = 3000;


// dp[i][j]  length is j, end with i, the valid count
int dp[N][N];

int n, x, y;
int main() {

    cin >> n >> x >> y;
    if (x > y) dp[y][1] = 1;
    else dp[x][1] = 1;

    for (int j = 1; j <= n; j ++)  {

        int res = 0;
        for (int i = j + 1; i <= n; i ++) {
            
        }
    }
    return 0;
}