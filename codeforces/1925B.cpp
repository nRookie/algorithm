#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


void solve() {
    int n,x ;

    cin >> x >> n;


    int ans = 1;

    for (int i = 1; i < x/ i; i ++) {
        if (x % i == 0) {
            if (n <= x/ i) {
                ans = max(ans, i);
            }
            if (n <= i)  ans = max(ans, x / i);
        }
    }

    cout << ans << '\n';
 
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}