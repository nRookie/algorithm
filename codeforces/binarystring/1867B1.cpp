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

    string s;
    cin >> s;

    string t (n + 1, '0');

    int ans = 0;
    int max_2 = 0;
    int max_1 = 0;

    for (int i = 0; i < n / 2; i ++) {
        if (s[i] == s[n - i - 1]) {
            max_2 ++;
        } else {
            ans ++;
        }
    }

    if (n % 2 == 1) {
        max_1 = 1;
    }

    for (int i = 0; i <= max_2; i ++) {
        for(int j = 0; j <= max_1; j ++) {
            t[ans + i * 2 + j] = '1';
        }
    }

    cout << t << '\n';
 
    
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}