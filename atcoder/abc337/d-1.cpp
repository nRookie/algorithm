#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

const int MAX_N = 2 * 1e5 + 10;
const int INF = 0x3f3f3f3f;
string s[MAX_N];
int n, m, k, l, sum, ans = INF;

int main(){
    // Input
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++) {
        cin >> s[i];
    }
    // check rows
    int ans = INF;
    for (int i = 0; i < n; i ++) {
        int l = sum = 0;
        for (int j = 0; j < m; j ++) {
            if (s[i][j] == 'x') {
                l = j + 1;
                sum = 0;
                continue;
            } 
            
            if (s[i][j] == 'o') {
                sum ++;
            }
            // 0 1 2
            // l   j
            // 
            if (j - l + 1 == k) {
                ans =min(ans, k - sum );
                if(s[i][l] == 'o') {
                    sum --;
                }
                l++;
            }
        }
    }

    for (int i = 0; i < m; i ++) {
        int l = sum = 0;
        for (int j = 0; j < n; j ++) {
            if (s[j][i] == 'x') {
                l = j + 1;
                sum = 0;
                continue;
            } 
            if (s[j][i] == 'o') {
                sum ++;
            }
            // 0 1 2
            // l   j
            // 
            if (j - l + 1 == k) {
                ans = min(ans, k - sum );
                if(s[l][i] == 'o') {
                    sum --;
                }
                l ++;
            }
        }
    }
    // Output
    if(ans == INF) {
        cout << -1 << "\n";
    }
    else {
        cout << ans << "\n";
    }

    return 0;
}
