#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;



int N,S,M ,L;

int dp[110]; // minimum money needed for buying N  eggs
int main() {
    scanf("%d%d%d%d", &N, &S, &M, &L);
    memset(dp, 0x3f, sizeof dp);
    for (int i = 1; i <= 6; i ++) dp[i] = min(min(L,M), S);
    for (int i = 7 ; i <= 8; i ++) dp[i] = min(L, min(2 * S, M));
    for (int i = 9 ; i <= 12; i ++) dp[i] = min(L, min(2 * S, 2 * M)); 
    // for (int i = 1; i <= 12; i ++) {
    //     cout << i << " " << dp[i] << endl;
    // }
    for (int i = 13; i <= N; i ++) {
        dp[i] = min(min(dp[i - 6] + S, dp[i - 8] + M ), dp[i - 12] + L);
        //cout << dp[i] << endl;
    }

    cout << dp[N] << endl;

    return 0;

}