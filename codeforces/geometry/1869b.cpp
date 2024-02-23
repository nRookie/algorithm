#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;



const int N = 2* 1e6 + 10, M = 4 * N;
int h[N], ne[M], e[M], w[M], idx;

void add (int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}


typedef long long ll;

typedef pair<ll,ll> PII;
ll exgcd(ll a, ll b, ll & x, ll&  y) {
    
        if (b == 0) {
            x = 1;
            return a;
        }
        ll d = exgcd(b, a % b, y , x);
        y -= a/b * x;  
        
        return d;
}



// 
// n cities on the plane. 1 to n, first k defined as major cities.

// i-th city are(xi, yi)

// a -> b by air
// 
//  i, j are both major cities.
//
void solve() {
    ll n, k, x, y;
    cin >> n >> k >> x >> y;
    vector<PII>  coord(n + 1);
    for (int i = 1; i <= n; i ++) {
        ll a, b;
        cin >> a >> b;
        coord[i] = {a, b};
    }

    ll res = abs(coord[x].first - coord[y].first) + abs(coord[x].second - coord[y].second);

    if (k == 0) {
        cout << res << endl;
        return ;
    }

    ll dist1 = LLONG_MAX; // a -> major city
    for (int i = 1; i <= k; i ++) {
        dist1 = min(dist1,  abs(coord[x].first - coord[i].first) +   abs(coord[x].second - coord[i].second));
    }


    ll dist2 = LLONG_MAX; // b -> major city
    for (int i = 1; i <= k; i ++) {
        dist2 =  min(dist2,  abs(coord[y].first - coord[i].first) +   abs(coord[y].second - coord[i].second));
    }
    res = min(res, dist1 + dist2);

    cout << res << endl;
    return ;
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}