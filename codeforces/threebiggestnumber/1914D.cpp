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
// go skiing,  ai,
// movie ,  bi 
// play board game, ci

// 
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1), c(n + 1);

    int mxa1 = -1, mxa2 = -1, mxa3= -1;
    int mxb1 = -1, mxb2 = -1, mxb3= -1;
    int mxc1 = -1, mxc2 = -1, mxc3= -1;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        if (mxa1 == -1 ||  a[mxa1] < a[i]) {
            mxa3 = mxa2;
            mxa2 = mxa1;
            mxa1 = i;
        } else if (mxa2 == -1 || a[mxa2] < a[i]) {
            mxa3 = mxa2;
            mxa2 = i;
        } else if (mxa3 == -1 || a[mxa3] < a[i]) {
            mxa3 = i;
        }
    }

    for (int i = 1; i <= n; i ++) {
        cin >> b[i];
        if (mxb1 == -1 ||  b[mxb1] < b[i]) {
            mxb3 = mxb2;
            mxb2 = mxb1;
            mxb1 = i;
        } else if (mxb2 == -1 || b[mxb2] < b[i]) {
            mxb3 = mxb2;
            mxb2 = i;
        } else if (mxb3 == -1 || b[mxb3] < b[i]) {
            mxb3 = i;
        }
    }
 
    for (int i = 1; i <= n; i ++) {
        cin >> c[i];
        if (mxc1 == -1 ||  c[mxc1] < c[i]) {
            mxc3 = mxc2;
            mxc2 = mxc1;
            mxc1 = i;
        } else if (mxc2 == -1 || c[mxc2] < c[i]) {
            mxc3 = mxc2;
            mxc2 = i;
        } else if (mxc3 == -1 || c[mxc3] < c[i]) {
            mxc3 = i;
        }
    }


    vector<int> indexa = {mxa1, mxa2, mxa3};
    vector<int> indexb = {mxb1, mxb2, mxb3};
    vector<int> indexc = {mxc1, mxc2, mxc3};

    int res = 0;
    for (int x = 0; x < 3; x ++)
        for (int y = 0; y <3; y ++)
            for (int z = 0; z < 3; z ++) {
                if (indexa[x] != indexb[y] && indexb[y] != indexc[z] && indexa[x] != indexc[z]) {
                    res = max(res,a[indexa[x]] + b[indexb[y]] + c[indexc[z]]  );
                }
            }

    cout << res << endl;


}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}