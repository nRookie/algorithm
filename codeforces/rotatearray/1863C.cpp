#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<queue>
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
// a1,a2,..., an 
// ai .... an with MEX(a1,a2, ..., an);

// here MEX of a collection of integers c1, c2, ..., cm is defined as the smallest non-negative integer x which does not occur in the collection c
// For example, MEX(0,2 ,2 ,1, 4) = 3 and MEX(1, 2) = 0

// 
void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n + 1);
    ll sum = 0;
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
        sum += a[i];
    }
    a[n] = n * (n + 1) / 2 - sum;


    k = k % (n + 1);

    // 0 1 3 2
    // 2 1 3 0
    // 2 0 3 1
    // 2 0 1 3
    // 
    vector<ll> b(n + 1, 0);
    for (int i = 0; i < n + 1 ; i ++) {
        b[(i + k) % (n + 1)] = a[i];
    }

    // 0 1 3 2
    // 

    for (int i = 0; i < n; i ++)
        cout << b[i] << " ";
    cout << '\n' ;


 
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}