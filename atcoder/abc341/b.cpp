#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;



const int N =  2 * 1e6 + 10, M = 4 * N;

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


// N countries,  i = 1,2,...,N.
// Ai units of currency of country i

// 1. choose an integer between 1 and N - 1. inclusive

// 2. has at least Si units of the currency of country i, he performs the follwing action once.

// - pay Si units of the currency of country i and gain Ti units of the currency of country(i + 1).


int n;

ll a[N];
int s[N], t[N];

int main() {
    cin >> n;

    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    for (int i = 1; i < n; i ++) {
        cin >> s[i] >> t[i];
        if (a[i] >= s[i]) {
            ll count = a[i] / s[i];
            a[i + 1] += count * t[i];
        }
    }

    cout << a[n] << endl;

    return 0;
}