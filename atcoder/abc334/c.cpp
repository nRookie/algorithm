#include<iostream>
#include<cmath>
#include<vector>
using namespace std;


const int N = 3e5 + 10;
int a[N];

int pre[N];
int suf[N];


int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i ++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i ++) {
        pre[i] = pre[i - 1];
        if( (i % 2) == 0) {
            pre[i] += a[i - 1] - a[i - 2];
        }
        
    }
    // m = 5 , m + 1 = 6
    // 0 1 2 3 4 5
    // 1 2 3 4 5  a[i]
    //           0   suf
    for (int i = m - 1 ; i >= 0; i -- ) {
        suf[i] = suf[i + 1];
        if((m - i) % 2 == 0) {
             suf[i] += a[i + 1] - a[i];
        }
        
    }

    // for (int i = 0; i <= m; i ++) 
    //     cout << pre[i] << " ";
    // cout << endl;
    // for (int i = 0; i <= m; i ++) 
    //     cout << suf[i] << " ";
    // cout << endl;
    int res = 1e9;
    for (int i = 0; i <= m; i += 2 ) {
        res = min(res, pre[i] + suf[i]);
    }
    cout << res << endl;
    return 0;
}