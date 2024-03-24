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
    vector<int> a(n), b(n),  fa(n + 1), fb(n + 1);
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i ++) {
        cin >> b[i];
    }

    int p = 0;
    for (int i = 1; i < n; i ++) {
        if (a[i] != a[i - 1]) {
            fa[a[i - 1]] = max(fa[a[i - 1]], i - p);
        }
    }

    fa[a[n - 1]] = max(fa[a[n - 1]],  n - 1 - p);

    p = 0;
    for (int i = 1; i < n; i ++) {
        if (b[i] != b[i - 1]) {
            fb[b[i - 1]] = max(fb[b[i - 1]], i - p);
        }
    }

    fa[b[n - 1]] = max(fb[b[n - 1]],  n - 1 - p);
    int len = 0;

    for (int i = 0; i < n; i ++) {
        len = max(len, fa[i] + fb[i]);
    }
    
    cout << len << endl;
 
}


void solve1() {
    int n;
        cin >> n;
        vector<int> a(n + 1);
        vector<int> b(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i];
        }
        for (int i = 1; i <= n; ++i)
        {
            cin >> b[i];
        }
        vector<int> fa(n + n + 1);
        vector<int> fb(n + n + 1);
        int p = 1;
        for (int i = 2; i <= n; ++i)
        {
            if (a[i] != a[i - 1])
            {
                fa[a[i - 1]] = max(fa[a[i - 1]], i - p);
                p = i;
            }
        }
        fa[a[n]] = max(fa[a[n]], n - p + 1);

        p = 1;
        for (int i = 2; i <= n; ++i)
        {
            if (b[i] != b[i - 1])
            {
                fb[b[i - 1]] = max(fb[b[i - 1]], i - p);
                p = i;
            }
        }
        fb[b[n]] = max(fb[b[n]], n - p + 1);

        int ans = 0;
        for (int i = 1; i <= n + n; ++i)
        {
            cout << fa[i] << " " << fb[i] << endl;
            ans = max(ans, fa[i] + fb[i]);
        }

        cout << ans << '\n';
}

int main() {
    int t;
    cin >> t;

    while (t --) {
        solve1();
    }
}