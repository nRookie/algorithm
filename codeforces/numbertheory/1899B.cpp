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



// Br asked , 250 thousands tons of TNT,
// alex didn't hear him well.
// so he prepared nboxes and arranged them in a row waiting for trucks. The i-th box from the left weighs ai tons.
// ALl trucks that Alex is going to use hold the same number of boxes, denoted by k, loading happens the following way.
// the first k boxes goes to the first truck.
// second k , ->
// ... 
//, the last k box goes to the n/ k - th truck.

//
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
    }
 
    vector<ll> pre(n + 1);

    for (int i = 1; i <= n ; i ++) 
        pre[i] = pre[i - 1] + a[i - 1];

    // 1 2 3 4 5 6
    // 0 1 3 6 10 15 21
    // 
    ll ans = 0;
    for (int k = 1; k < n; k ++) {
        ll maxx = 0, minn = LLONG_MAX;
        if (n % k == 0) {
            for (int i = k; i <= n; i += k) {
                maxx = max(pre[i] - pre[max(i - k, 0)], maxx);
                minn = min(pre[i] - pre[max(i - k, 0)], minn);
            }
        }
        ans = max(ans, maxx - minn);
    }
    cout << ans << endl;
}


void solve2() {
        int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    ll ans = -1;
    for (int d = 1; d <= n; ++d) {
        if (n % d == 0) {
            ll mx = -1e18, mn = 1e18;
            for (int i = 0; i < n; i += d) {
                ll sm = 0;
                for (int j = i; j < i + d; ++j) {
                    sm += a[j];
                }
                mx = max(mx, sm);
                mn = min(mn, sm);
            }
            ans = max(ans, mx - mn);
        }
    }
    cout << ans << '\n';
}
// 1 2
// 1 2 1
// 10 2 3 6 1 3 
// 15     10     5
// 12 8 4 
// 1000 1000 1 1
// 2000 2
int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}