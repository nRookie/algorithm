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


vector<int> get_divisors(int n) {
    vector<int> res;

    for (int i = 1; i <= n / i; i ++) 
        if (n % i == 0) {
            res.push_back(i);
            if (i != n / i) res.push_back(n / i);
        }

    sort(res.begin(), res.end());
    return res;

}


ll gcd(ll a, ll b) {
    if ( b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}
void solve() {

    long long a = 0,b = 0;
    cin >> a >> b;

    if (b % a == 0) {
        cout  << b * b / a << '\n';
    } else {
        cout <<  b * a / gcd(a,b) << '\n';
    }
    //   b % a == 0
    //   b = a * p
    // 1 2
    // 2 = 1 * 2
    // 
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}