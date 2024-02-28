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
    int n, x;
    cin >> n >> x;
    vector<int> a(n), b(n), c(n);
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
        //if (i) a[i] = a[i] | a[i - 1];
    }

    int l1 = 0, r1 = n;

    for (int i = 0; i < n; i ++) {
        cin >> b[i];
        //if (i) b[i] = b[i] | b[i - 1];
    }

    for (int i = 0; i < n; i ++) {
        cin >> c[i];
        //if (i) c[i] = c[i] | c[i - 1];
    }

    int as = 0, bs = 0, cs = 0;
    int ai = 0, bi = 0, ci = 0;
    while ( ai < n && ( (x | a[ai]) == x)) {
        as |= a[ai];
        ai ++;
    }

    while ( bi < n && ( (x | b[bi]) == x)) {
        bs |= b[bi];
        bi ++;
    }

    while ( ci < n && ( (x | c[ci]) == x)) {
        cs |= c[ci];
        ci ++;
    }

    if ( ( as | bs | cs ) == x ) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
 
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}