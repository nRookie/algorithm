#include<iostream>
#include<vector>
#include<algorithm>
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



// a, 
// 
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end()) ;
    a.resize(unique(a.begin(), a.end()) - a.begin() );

    int left = 0;
    // 1 2 3 4
    // 4 - 1 = 3 
    // 3 >= 3 
    int ans = 0;
    for (int i = 0; i < a.size(); i ++) {
        while (a[i] - a[left] >= n) {
            left ++;
        }

        ans = max(ans, i - left + 1);
    }

    cout << ans << endl;
}

void solve1() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    a.resize(unique(a.begin(), a.end()) - a.begin());
    int pnt = 0, ans = 0;
    for (int i = 0; i < a.size(); i++) {
        while(a[i] - a[pnt] >= n) {
            pnt++;
        }
        ans = max(ans, i - pnt + 1);
    }
    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}