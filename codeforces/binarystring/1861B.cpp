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
    string a, b;
    cin >> a >> b;

    for (int i = 0; i < a.size() - 1; i ++) {
        if (a[i] == b[i] && a[i] == '0' && a[i + 1] == b[i + 1] && a[i + 1] == '1') {
            std::cout << "YES" << endl;
            return ;
        }
    }

    std::cout << "NO" << endl;
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}