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
// has an array a of n integers, the elements are numbered from 1 to n.

// 2 <=i <= n - 1
// ai - 1 = ai - 1 - 1
// ai = ai - 2
// ai+1 = ai+ 1 - 1
// 
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
    }

    for (int i = 0 ; i < n - 2; i ++) {
        if (a[i] > 0) {
            a[i + 1] -= a[i] * 2;
            a[i + 2] -= a[i];
            a[i] = 0;
            if (a[i + 1] < 0 || a[i + 2] < 0) {
                cout << "NO" << endl;
                return;
            }
        }
    }

    // if (a[n - 1] != 0 || a[n - 2] != 0 ) cout << "NO" << endl;
    for (int i = 0; i < n; i ++) {
        if (a[i] != 0) {
             cout << "NO" << endl;
             return ;
        }
    }
    cout << "YES" << endl;
    // 1 3 5 5 2
    // 0 1 4 5 2
    // 0 0 2 4 2
    // 
 
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}