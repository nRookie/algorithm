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
// 6 4 3 5 2 1 
// 3 2 1 6 4 5
// 
void solve() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i ++) {
        cin >> p[i];
    }
    int k = 0;

    set<int> ss;

    for (int i = 0; i < n; i ++)  {
        if (ss.count( p[i] + 1)) {
            k ++;
        }
        ss.insert(p[i]);
    }

    cout << k << endl;
 
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}