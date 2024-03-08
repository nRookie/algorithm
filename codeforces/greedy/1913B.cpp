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
    // delete one character from s, cost 1 .
    // swap any pair of characters in s. 
    // 0
    string s;
    int cnt[2] = {0};

    cin >> s;

    for (auto c : s) cnt[c - '0'] ++;
    int n = s.size() ; 
    string t;

    for (int i = 0; i < n; i ++) {
        if (cnt[ (s[i] - '0') ^ 1] > 0) {
            t += (char((s[i] - '0' ^ 1) + '0'));
            cnt[ (s[i] - '0') ^ 1] --;
        } else {
            break;
        }
    }

    cout << s.size() - t.size() << endl;
    // 111100
    // 001111
    // 000011

}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}