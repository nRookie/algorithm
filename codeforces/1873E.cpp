#include<iostream>
#include<vector>
#include<algorithm>
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

bool check(vector<int> &a, ll h, ll water) {
    ll sum = 0;
    for (int i = 0; i < a.size(); i ++) {
        if (h - a[i] > 0) {
            sum += h - a[i];
        }
    }
    // cout << h << " " << sum << " " << water << endl;
    return (sum <= water);
}
void solve() {
    ll n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
    }


    ll l = 1 , r = 2e9 + 10000;

    while (l < r) {
        ll mid = (l + r + 1) >> 1;
        if (check(a, mid, x)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    cout << l << endl;

    // length * (h - a[i]) <= water
    // 
    // if (a[mid] <= k) {
    //       r = mid;
    // } else {
    //       l = mid + 1;
    // }

    // l     l r  
    // l       0       r
    // 0 1 2 3 4 5 6 7 8
    // 1 2 3 4 4 4 5 6 7
    // l       m       r  
    // 
    // 
}


// 3 1 2 4 6 2 5
// 3 1 2 4 6 2 5

//

int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }


}