#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;



const int N = 2* 1e6 + 10, M = 4 * N;

typedef pair<int,int> PII;
int h[N], ne[M], e[M], w[M], idx;

void add (int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}


typedef long long ll;
ll exgcd(ll a, ll b, ll & x, ll&  y) {
    
        if (b == 0) {
            x = 1;
            return a;
        }
        ll d = exgcd(b, a % b, y , x);
        y -= a/b * x;  
        
        return d;
}



// a, 
// 
void solve() {
    int n;
    cin >> n;
    vector<ll> a(n);
    vector<ll> f(n);
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
    }

    f[0] = a[0];
    ll res = a[0];
    for (int i = 1; i < n ; i ++) {
        if ( (a[i] & 1 ) != (a[i - 1] & 1) ) {
            f[i] = max(f[i - 1] + a[i], a[i]);
        } else {
            f[i] = a[i];
        }
        res = max(res, f[i]);
     }


     cout << res << endl;

}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}