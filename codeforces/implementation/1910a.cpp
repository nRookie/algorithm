#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;



const int N = 1e6 + 10, M = 4 * N;

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
// lowercase, and/or digits

// positive integer without leading zeros is appended to the ned of the username.
// user, us

// 
void solve() {
    string s;

    cin >> s;
    int n = s.size();
    int alphaEndIndex = -1;
    for (int i = n - 1; i >= 0 ; i --) {
        if (s[i] >= 'a' && s[i] <= 'z')  {
            alphaEndIndex = i;
            break;
        }
    }

    int zeroEndIndex;
    for (int i = alphaEndIndex + 1 ; i < n ;  i ++) {
        if (s[i] != '0') {
            zeroEndIndex = i;
            break;
        }
    }

    cout << s.substr(0, zeroEndIndex) << endl;
    // 0,
    // 1
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}