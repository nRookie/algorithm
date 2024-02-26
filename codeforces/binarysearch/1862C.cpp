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
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }
    if (a[1] != n) {
        cout << "NO" << endl;
    } else {
        vector<int> b(n + 1);
        vector<int> c = a;
        // for (auto x:  c) cout << x << " ";
        // cout << endl;
        reverse(c.begin() + 1, c.end());
        // for (auto x:  c) cout << x << " ";
        // cout << endl;
        for (int i = 1; i <= n; i ++) {


            int l = 0, r = n ;
            // 1 2 3 4 5
            // l   mid r           i
            //                       i >= c[mid]
            //                     
            // 1 1 3
            // l   r
            // 
            while (l < r) {
                int mid = l + r + 1 >> 1;
                if (i > c[mid]) {
                    l = mid;
                } else { // i <= c[mid]
                    r = mid - 1;
                }
            }
            b[i] = n - l;
        }

        // for (int i = 1; i <= n; i ++) cout << b[i] << " " ;
        // cout << endl;

        for (int i = 1; i <= n; i ++) {
            if (a[i] != b[i]) {
                cout << "NO" << endl;
                return ;
            }
        }

        cout << "YES" << endl;
    }

}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}

// search where should we insert