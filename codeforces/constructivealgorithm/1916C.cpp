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



// a of size n, take turn
// size is one , end 
// choose two different indices, i, j , and performs the following operation
// a, maximize,
// b, minimize it
// 12 11
// 23 

// 7 7
// 14 

void solve() {
    int n;
    cin >> n;
    vector<int> v(n);

    for (int i = 0;  i < n; i ++) cin >> v[i];

    //After dividing the odd numbers by 3 (odd / 3), you correctly observe that it would be the first player's turn again because three moves have been made to form each set of three odd numbers, 
    ll sum = 0, odd = 0, even = 0;

    (v[0] & 1) ? odd ++ : even ++;
    sum = v[0];
    cout << sum << ' ';

    for (int i = 1; i < n; i ++) {
        if (v[i] & 1) odd ++;
        else even ++;
        sum += v[i];
        int cnt = odd / 3;
        int d = odd % 3;
        if (d & 1) cnt ++;
        cout << sum - cnt << endl;
    }
    cout << '\n';
 
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}