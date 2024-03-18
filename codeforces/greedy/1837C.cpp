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



// 0, 1 and/or ?. Let's call it a pattern.
// ? with 1 or 0 . so that the string s become equal,      0010 matches ?01?

// but 010 doesn't match 1 ??, ?? , ????.


// cost ->  minimum number of operations of the form "reverse an arbitrary contiguous substring of the string"
// required to sort the string in non-descending order

// 11011
// 1111011
// 11101110
// 01111110
// 00111111
// 10100
// 01100
// 00011
//
void solve() { 
    string s;
    cin >> s;
    int n = s.size();
 
    char last = '0';
    for (int i =0; i < n; i ++) {
        if (s[i] != '?') {
            last = s[i];
            break;
        }
    }

    for (int i = 0; i < n; i ++) {
        if (s[i] == '?') {
            s[i] = last;
        } else {
            last = s[i];
        }
    }

    cout << s << endl;
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}