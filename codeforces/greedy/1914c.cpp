#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;



const int N = 1e6 + 10, M = 4 * N;

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




void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n + 1 );
    vector<int> b(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i ++) {
        cin >> b[i];
    }

    int sum = 0;
    int maxb = 0;
    int res = 0;
    for (int i = 1; i <= min(n, k); i ++) {
        sum += a[i];
        maxb = max(maxb,b[i]);
        res = max(res, sum + maxb * (k - i));
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