#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
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



int main() {

    int n;
    cin >> n;
    vector<int> w(n);
    vector<int> pre(n + 1);
    for (int i =0 ; i < n; i ++) cin >> w[i];

    for (int i = 1; i <= n; i ++) pre[i] = pre[i - 1] + w[i - 1];
    int res = INT_MAX;
    for (int T = 1; T<= n; T ++) {
        // cout << (pre[T] - pre[0])  << " " <<   (pre[n] - pre[T])  << endl;
        res = min(res, abs( (pre[T] - pre[0]) -  (pre[n] - pre[T])  ) );
    }
    // 0 1 2 3
    // 1 3 1 1
    // 0 1 4 5 6
    // 

    cout << res << endl;   
    return 0;
}