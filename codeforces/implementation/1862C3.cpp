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
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }
    if (a[1] != n) {
        cout << "NO" << endl;
        return ;
    }
    vector<int> b;
    for (int i = n; i >= 1; i --) {
        while(b.size() < a[i]) {
            b.push_back(i);
        }
    }


    for (int i = 1; i <= n; i ++) {
        if (b[i - 1] != a[i]) {
            cout << "NO" << endl;
            return ;
        }
    }

    cout << "YES" << endl;

}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}

// search where should we insert