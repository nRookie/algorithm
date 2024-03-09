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
    // a1, a2, ..., an//   
    // b1, b2, ..., bn

    // 1, 2, 3
    // exactly two out of the following three conditions are satisfied

    // 1 <= i, j <= n such that , ai = aj, bj = 1, bj = 2
    // 1 <= i, j <= n,   ai = aj, bi = 1, bj = 3
    // 1 <= i, j <= n, ai = aj, bj = 2, bj = 3

    vector<int> a(n);
    int cnt[101] = {0};
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    int find[2], findi = 0;
    for (int i = 1; i <= 100; i ++) {
       if (cnt[i] >= 2) {
         if (findi == 0) {
            find[findi] = i;
            findi ++;
         } else {
            find[findi] = i;
            findi ++;
            break;
         }
       }
    }
    if (findi == 2) {
        int x = 0;
        vector<int> b(n, 1);
        for (int x = 0; x < findi; x ++) {
            bool first = true;
            for (int i = 0; i < n; i ++) {
                if (a[i] == find[x]) {
                    if (first) {
                        b[i] = 1;
                        first = false;
                    } else {
                        b[i] = 2 + x;
                    }
                }
            }
        }
        for (auto x : b) cout << x << " ";
        cout << endl;
    }
    else 
    cout << -1 << endl;

}

// 0 1 2 3 4 5
// 1 3 1 4 1 5
// 1 1 2 1 3 1
// a1 = a2 = a3
// b1 = 1, b2 = 2, b3 = 3


// 

int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}