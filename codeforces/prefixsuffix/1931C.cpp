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
// j - i + 1

// 1,2,3,4,5,1
// 1 8 8 8 5 1
// 
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
    }

    int pre = 1, suffix = 1;
    
    for (int i = 1; i < n && a[i] == a[0]; i ++) {
        pre ++;
    }
 
     for (int i = n - 2; i >= 0 && a[i] == a[n - 1]; i --) {
        suffix ++;
    }
    if (a[0] == a[n - 1]) {
        cout << max(0, n - pre - suffix) << endl;
    } else {
        cout << min(n - pre, n - suffix) << endl;
    }
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}