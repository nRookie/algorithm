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
    int n, k, q;
    cin >> n >> k >> q;

    vector<int> a(n, 0);

    for (int i = 0; i < n; i ++) cin >> a[i];

    ll res = 0;
    int length = 0;
    for (int i = 0; i < n; i ++) {
        if (a[i] <= q) {
            length ++;
        } else { 
            if (length >= k) {
                res += (long long)(length - k + 1) * (length - k + 2) / 2;
            } 
            length = 0;
        }
    }

    if (length >= k) {
       res += (long long)(length - k + 1) * (length - k + 2) / 2;
    }

    cout << res << endl;
    return ;
 
}

// S = n / 2 * ([2 * a + (n - 1)d])
// (length - k  + 1) / 2 * (2 * (length - k + 1) + (length - k + 1 - 1) -1)
// (length - k + 1) / 2 * (2 * length - 2 * k + 2 - length + k )
// (length - k + 1) / 2 * (length - k + 2)


// (5,6),  (6,7)   (7, 8),   (8, 9)

int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}


// This sum is (l−k+1)+(l−k)+(l−k−1)+…+1, which is a sum of an arithmetic series.