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
    vector<int> a(n, (1 << 30) - 1);

    vector<vector<int>> g(n, vector<int> (n, 0));

    for (int i = 0; i < n; i ++)
        for (int j = 0; j < n; j ++)
            cin >> g[i][j];
    

    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            if (i != j) {
                a[i] &= g[i][j];
                a[j] &= g[i][j];
            }
        }
    }


    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            if (i != j) {
                if ( (a[i] | a[j]) !=  g[i][j]) {
                    cout << "NO" << endl;
                    return ;
                }
            }
        }
    }

    cout << "YES" << endl;

    for (auto x : a) {
        cout << x << " ";
    }
    cout << endl;
 
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}
