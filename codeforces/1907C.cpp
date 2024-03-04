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
    ll n;
    cin >> n;

    string s;

    cin >> s;
    int keep = 0;
    //012345
    // aabc
    // abaca
    // avbvvcvvvd
    // bbbcbbbcc
    ll cnt[26] = {0};
    for (auto & c : s) {
        cnt[c - 'a'] ++;
    }
    ll maxx = 0;

    for (int i = 0; i < 26; i ++) maxx = max(maxx, cnt[i]);

    // abaca
    // 5 - 3 = 2
    // 10 - 5 = 5
    ll other = n - maxx;
    if (maxx  > n / 2) {
        cout << maxx - other << endl;
    } else {
        cout << n % 2 << endl;
    }
    
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}