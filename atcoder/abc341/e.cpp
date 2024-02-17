#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;



const int N = 5 * 1e6 + 10, M = 4 * N;

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



// 0 and 1 is good string
// two consecutive characters in the strings are always different.

// S, 0, 1,  Q, queries

// in order.

// 

int n, m;
int s[N];

bool check(int l, int r) {

    for (int i = l; i < r; i ++) {
        cout << s[i];
    }

    cout << s[r] << endl;
    for (int i = l; i < r; i ++) {
        if (s[i] == s[i + 1]) {
            return false;
        }
    }
    return true;
}
int main() {
    cin >> n >> m;
    
    for (int i = 1; i <= n; i ++) {
        char c;
        cin >> c;
        s[i] = c - '0';
    }

    while (m --) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) {
            s[l] ^= 1;
            s[r] ^= 1;
        } else {
            if (check(l, r)) {
                cout << "Yes" << endl;
            } else {
                cout << "No" <<endl;
            }
        }
    }
    return 0;
}