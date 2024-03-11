#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
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
int n, m, x;
set<int> res;
vector<PII> operation;
void dfs(int u, int x) {
    // cout << u <<  " " << x << endl;
    if (u == m) {
        res.insert(x);
        return;
    }
    int dist = operation[u].first, dir = operation[u].second;
    if (dir == 3) {
       dfs(u + 1, (x + dist) % n );
       dfs(u + 1, (x - dist + n ) % n);
    } else if (dir == 1) {
        dfs(u + 1, (x - dist + n ) % n);
    } else {
        dfs(u + 1, (x + dist) % n );
    }

}
void solve() {
    res.clear();
    cin >> n >> m >> x;
    x-=1;
    operation.clear();
    for (int i = 0; i < m; i ++) {
        int a, b;
        char c;
        cin >> a;
        cin >> c;
        b = c - '0';
        if (c == '?') b = 3;
        // cout << a << " " << b << endl;  
        operation.push_back({a, b});
    }

    dfs(0, x);
    cout << res.size() << endl;

    for (auto x: res) cout << (x + 1) % (n + 1)<< " ";
    cout << endl;
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}