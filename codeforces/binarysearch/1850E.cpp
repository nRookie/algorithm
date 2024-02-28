#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<limits>
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
    ll n, c;
    cin >> n >> c;
    vector<ll> a(n);
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
    }
 
    ll l = 1, r = 1e9;
    while (l < r) {
        ll mid = (l + r) / 2;
        ll sum = 0;
        for (int i = 0; i < n; i ++) {
            sum = sum + (a[i] + 2 * mid) * (a[i] + 2 *  mid);
            if (sum > c) break;
        }
        //cout << sum << " " << l << " " <<  r << " " << mid <<  endl;
        if (sum < c) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    // cout << l << " " <<  r << endl;
    cout << r << endl;
}

int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}

