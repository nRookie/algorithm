#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<map>
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
// n sticks

//  , length of i stick is  2^ai

// 3 sticks out of the given nstikcs, and form a non-degenerate 
void solve() {
    int n;
    cin >> n;

    map<int, int> numOfLens;

    for (int i = 0; i < n; i ++) {
        int x;
        cin >> x;
        ++numOfLens[x];
    }
    ll sum = 0, res = 0;
    for (auto it : numOfLens) {
        ll cnt = it.second;
        if (cnt >= 3) {
            res += (cnt) * (cnt - 1) * (cnt- 2) / 6;
        }
        if (cnt >= 2) {
            res += (cnt ) * (cnt - 1) / 2 * sum;
        }
        sum += cnt;
    }

    cout << res << '\n';
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}