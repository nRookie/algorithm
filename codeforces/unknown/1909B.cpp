#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<set>
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
// integer k
// i from 1 to n, Replace ai with ai mod k
void solve() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
    }

    ll xi = 2;
    int i = 0;
    while(i <= 57) {
        set<ll> ans;
        for (auto x : a) {
            ans.insert(x % xi);
        }
        if (ans.size() == 2) {
            cout << xi << endl;
            return;
        }
        xi *= 2;
        i ++;
        ans.clear();
    }

    // Therefor it is sufficient to try
 
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}