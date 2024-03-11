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
    vector<vector<int>> a(n);
    int x = 1e9 + 1;
    for (int i = 0; i < n; i ++) {
        int m;
        cin >> m;
        a[i] = vector<int>(m);
        for (int j = 0; j < m; j ++) cin >> a[i][j];

        sort(a[i].begin(), a[i].end());
        x = min(x, a[i][0]);
    }

    sort(a.begin(), a.end(), [&](vector<int> x, vector<int> y){
        return x[1] < y[1];
    });
 
    long long res = x;

    for (int i = 1; i < n; i ++) res += a[i][1];

    cout << res << endl;
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}