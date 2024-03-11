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


void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
    }

    int p1 = 0;
    vector<int> st(n);
    int left = 0;
    for (int i = 0 ; i < n; i ++) {
        if (!st[i] && a[i] == a[0]) {
            st[i] = true;
            p1++;
            if (p1 == k) {
                left = i;
                break;
            }
        }
    }

    if (a[0] == a[n - 1] && p1 == k) {
        cout << "YES" << endl; 
    } else {
        if (p1 < k) {
            cout << "NO" << endl;
            return ;
        }
        int p2 = 0;
        for (int i = n - 1 ; i > left ; i --) {
            if (!st[i]&& a[i] == a[n - 1]) {
                st[i] = true;
                p2++;
                if (p2 == k) {
                    break;
                }
            }
        }
        if (p2 == k) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
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