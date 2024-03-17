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
    int big = n;
    int small = 1;
    int count = 0;
    while (count < n) {
        cout << big << " ";
        big -= 1;
        count ++;
        if (count < n) {
            cout << small << " ";
            small += 1;
            count ++;
        }
    }
    cout << endl;
}

void solve1() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i ++) {
        cout << i << " ";
    }

    cout << endl;
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve1();
    }
}