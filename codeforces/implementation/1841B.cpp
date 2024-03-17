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
// rotate and becoming a non descending array -> beautiful
// 



//
void findTurningPoint() {
    int n;
    cin >> n;
    vector<int> a (n);
    for (int i = 0; i < n ; i ++) cin >> a[i];

    // 3 4 5 1 2
    // l       r
    //     m
    //     l   r
    //       m
    //       
    // 0 1 2 3 4
    // a[0] < a[m]
    // 
    // int l = 0, r = n - 1;
    int l = 0 , r = n - 1;

    while (l < r) {
        int m = l + r + 1 >> 1;
        // cout << m << endl;
        if (a[0] <= a[m]) {
            l = m;
        } else {
            r = m - 1;
        }
    }

    cout << r + 1<< endl;

}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    string res(n, '0');

    bool turned = false;
    int tail = -1;
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
        if (i) {
            if (turned) {
                if (a[i] <= a[0] && a[i] >= tail) {
                    tail  = a[i];
                    res[i] = '1';
                }
            } else {
                if (a[i] >= tail ) res[i] = '1', tail = a[i];
                else if (a[i] <= a[0]) turned = true, tail = a[i], res[i] = '1';
            }
        } else {
            res[i] = '1';
            tail = a[i];
            
        }
        // cout << a[i] << " " << tail << " " << turned <<  endl;
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