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
    int n;
    cin >> n;
    vector<int> a(n);


    if (n < 2) {
        cout << 1 << endl;
        return ;
    }   
    if (n == 2) {
        cout << 2 << " " << 1 << endl;
        return ;
    } 
    a[0] = 2;
    a[n - 1] = 3;

    a[(n) / 2] = 1;
    int num = 4;
    for (int i = 1; i < n - 1; i ++) {
        if (a[i] == 0) {
            a[i] = num++;
        }
    }

    for (int i = 0; i < n; i ++) cout << a[i] << " " ;
    cout << endl;
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}