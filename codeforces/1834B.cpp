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
    int l, r;

    cin >> l >> r;

    vector<int> numl, numr;

    while(l) {
        numl.push_back(l % 10);
        l /= 10;
    }
    while (r) {
        numr.push_back(r % 10);
        r /= 10;
    }
    int k = numr.size() - numl.size();
    if (numl.size() != numr.size()) {
        numl.insert(numl.begin(), k, 0);
    }

    // 1000      1
    // 1230    0001
    // 
    long long res = 0;
    for (int i = 0; i < k; i ++) {
        res += numr[i];
    }

    for (int i = k; i < numr.size(); i ++) {
        res += numr[i];
    }
 
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}