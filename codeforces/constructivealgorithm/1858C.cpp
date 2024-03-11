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


ll gcd(ll a, ll b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// 1 2 3 4 5 6 7 8
// 1 2 4 8 6 3 7
// 1 1 2 4 2 3 1


// 1 2 4 8 
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);

    vector<int> st(n + 1);
    cout << 1 << " ";
    for (int i = 2; i <= n; i ++) {
        for (int j = i; j <= n; j += j) {
            if(!st[j]) {
                st[j] = true;
                cout << j << " ";
            }
        }
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