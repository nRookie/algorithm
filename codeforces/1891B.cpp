#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//  a of n, 
//  b of length q
// 

typedef long long ll;
// 5 3
// 1 2 3 4 4
// 2 3 4

// 
void solve() {
    int n, q;
    cin >> n >> q;
    vector<ll> a(n, 0);
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
    }
    vector<int> x(n, 0 );


    for (int i = 0; i < q; i ++) {
        cin >> x[i]; 
    }

    int minx = 31;

    for (int i = 0; i < q; i ++) {
        if (x[i] < minx) {
            minx = x[i];
            for (int j = 0; j < n; j ++)  {
                if (a[j] % ( 1 << minx) == 0) {
                    a[j] += (1 << (minx - 1) );
                }
            }
        }
    }

    for (int i = 0; i < n; i ++) {
        cout << a[i] << " ";
    }
    cout << endl;

}



int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}