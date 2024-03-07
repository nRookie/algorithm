#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
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

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

ll lcm(ll a, ll b) {
    return (ll)(a * b) / gcd(a, b);
}

ll range_sum(ll l, ll r) {
    if (l > r) return 0;
    return (ll) (l + r) * (r - l + 1) / 2;
}
void solve() {
    ll n , x , y;
    cin >> n >> x >> y;
    ll l = lcm(x, y);
    ll plus = (n / x) - (n / l);
    ll minus = (n / y) - (n / l);
    cout << range_sum(n - plus + 1, n) - range_sum(1, minus)<< endl;
    // 7 2 3
    // 1 2 3 4 5 6
    //   2   4   6     red        red but not purple 2
    //     3     6     blue
    //           6     purple

    // red - puple
    // blue - purple
    // n + n - 1 + ... n - (R - 1)) 
    // n + (n - 1) + .. + n - (R - 1)
    // - (1 + 2 + .. + B)
    // 
}
int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}