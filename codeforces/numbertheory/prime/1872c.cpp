#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
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
// l < a + b < r
// gcd(a, b) = 1


ll gcd(ll a, ll b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}


int getComposite(int x) {
    for (int i = 2; i <= x / i; i ++) {
        if (x % i == 0) return i;
    }
    return -1;
}

void solve() {
    int l, r;
    cin >> l >> r;
    if (r <= 3) {
        cout << -1 << endl;
        return ;
    }

    for (int x = l; x <= r; x ++) {
        for (int i = 2; i <= sqrt(x); i ++) {
            if (x % i == 0)  {
                cout << i << " " << x - i << endl;
                return ;
            }
        }
    }
    cout << -1 << endl;
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}