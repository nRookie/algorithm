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



// a number binary representation,   consisting of exacly n bits possibly with leading zeroes
// n = 5, the number 6 will be given as 00110, and for n = 4, the number 9 will be given as 1001
// 
void solve() {
    int n;
    cin >> n;
    string s ;

    cin >> s;

    reverse(s.begin(), s.end());

    int maxn = 0;
    for (int i = 0; i < n; i ++) {
        if (s[i] == '1') {
            maxn = max(maxn, i);
        }
    }
    // 10
    // 111100000
    // 01111
    // 001111000
    // 000111100
    // 000011110
    // 00000
    // 111100000
    //  11110000
    // 
    // 

    // cout << s << endl;
    ll res = 0;
    int j = 0;
    for (int i = 1; i <= n; i ++) {
        if (s[i - 1] == '0' ) {
            cout << res << ' ';
        } else {
            j = max(j, i);
           while (j < n) {
                if (s[j] == '0') {
                    res += j - (i - 1) ;
                    swap(s[i - 1], s[j]);
                    break;
                }
                j ++;
           } 
           if (s[i - 1] == '0') {
             cout << res << " ";
           } else {
             cout << -1 << " ";
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