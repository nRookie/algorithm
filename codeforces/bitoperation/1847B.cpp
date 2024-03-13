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
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
    }
    vector<int> pre(n + 1);
    int group = 0;
    pre[1] = a[0];
    for (int i = 2; i <= n; i ++) {
        if (pre[i - 1] == 0) {
            pre[i] = a[i - 1];
            group ++;
        } else  pre[i] = pre[i - 1] & a[i - 1];
    }

    if (pre[n] == 0) group ++;
    cout << max(1, group) << endl;
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}