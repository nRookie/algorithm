#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<map>
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
// 6 4
// 2 4
// 



// f[i][j]
// 

map<PII, bool>  myhash;
bool dfs(int n, int m) {
    if (n == m) {
        return true;
    }
    if (myhash.count({n, m}) ) return myhash[{n, m}];

    if (n < m ) return false;
    bool res = false;
    if (n % 3 == 0) {
        res |= dfs(n / 3, m);
        res |= dfs(n * 2 / 3, m);
    }
    myhash[{n, m}] = res;
    return  res;
}
void solve() {
    int n, m ;
    cin >> n >> m;
    if (dfs(n, m)) {
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