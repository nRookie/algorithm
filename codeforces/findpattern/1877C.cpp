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



//  chaneka
// n + 1 slots numbered from 1 to n + 1 from left to right
// n + 1 slots are going to to be filled by an array of non-negative integers 
//must assign an + 1 with an integer between 0 and m inclusive
//then for each i from n to 1, the value of ai will be equal to the remainder of dividing ai + 1

// ai = ai+1 mod i


//there are exactly k distinct values in the entire screen, (among all n + 1 slots). how many valid ways are there for assigning a non-negative integer into slot n + 1?

// 
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    if (k > 3) {
        cout << 0 << '\n';
        return;
    }

    if (k == 1) {
        cout << 1 << '\n';
        return;
    }
    if (m == 0) {
        cout << 0 << '\n';
        return ;
    } else if(k == 2) {
        if (m <= n) {
            cout << m << '\n';
            return ;
        } else {
            cout << n + (m - n) / n << '\n';
            return ;
        }
    } else {
        if (m <= n) {
            cout << 0 << '\n';
        } else {
            cout << m - n - (m - n) / n << '\n';
            return;
        }
    }
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}