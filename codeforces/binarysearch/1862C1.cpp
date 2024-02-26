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
    if (a[0] != n) {
        cout << "NO" << endl;
    } else {
        vector<int> b(n);
        for (int i = 0; i < n; i ++) {


            int l = 0, r = n;
            // 5 4 3 2 1
            // l   mid r         
            //                     
            // 1 1 3              i > a[mid]
            // l   r
            // 
            // l = 0, r = n
            while (l < r) {
                int mid = l + r>> 1;
                if (i >= a[mid]) {
                    r = mid;
                } else { // i <= c[mid]
                    l = mid + 1;
                }
            }
            b[i] = l;
        }

        // for (int i = 0; i < n; i ++) cout << b[i] << " " ;
        // cout << endl;

        for (int i = 0; i < n; i ++) {
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