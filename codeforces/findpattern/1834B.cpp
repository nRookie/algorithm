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



// a, 
// 
void solve() {
    string l, r;

    cin >> l >> r;

    int n = r.size();
    int k = r.size() - l.size();
    l = string(k, '0') + l;

    // 0001 1440
    // 
    long long res = 0;
    int diff = n - 1;
    for (int i = 0; i < n; i ++) {
        if (l[i] != r[i]) {
            diff = i;
            break;
        }
    }
    // cout << l << endl;
    // cout << r << endl;
    // cout << diff << endl;
    res += r[diff] - l[diff] + 9 * (n - diff - 1);
    cout << res << endl;
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}