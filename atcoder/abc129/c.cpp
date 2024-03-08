#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;



const int N = 1e6 + 10, M = 4 * N;
const int mod = 1000000007;

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


// staircase with N steps.

// at the foot of the stairs, that is on the 0th step
// he can climb up one or two steps at a time.
// how ever the treads of 

int main() {
    int n, m;

    cin >> n >> m;

    vector<int> a(m + 1, 0);
    vector<int> f(n + 1, 0);
    set<int> broken;
    for (int i = 1; i <= m; i ++) {
        cin >> a[i];
        broken.insert(a[i]);
    }


    f[0] = 1;
    if(!broken.count(1)) f[1] = 1;


    for (int i = 2; i <= n; i ++) {
        if (!broken.count(i)) {
            if (!broken.count(i - 1)) f[i] = f[i - 1] % mod;
            if (!broken.count(i - 2)) f[i] = (f[i] % mod + f[i - 2]  % mod )% mod;
        }
    }

    // for (int i = 0; i <= n; i ++) cout << f[i] << " ";
    // cout << endl;

    cout << f[n] % mod << endl;

    return 0;

}