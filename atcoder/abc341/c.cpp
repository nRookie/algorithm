#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;



const int N = 600, M = 4 * N;

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



// H rows, W columns

// land, or sea
// land  = .
// sea = #

// 

int n, m, n1;
string s;
char g[N][N];

int getLoc(int x, int y) {
    return x * m + y;
}



bool bfs(int sx, int sy) {
    vector<bool> st(n * m + 1);

    st[getLoc(sx, sy)] = true;
    

    queue<pair<int,int> > q;
    q.push({sx, sy});
    int i = 0;
    while (q.size()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        int a, b;
        if (s[i] == 'L' ) {
            a = x, b = y - 1;
        } else if (s[i] == 'R') {
            a = x, b = y + 1;
        } else if (s[i] == 'U') {
            a = x - 1, b = y;
        } else if (s[i] == 'D') {
            a = x + 1, b = y;
        }

        if (a < 0 || b < 0 || a >= n || b >= m  || g[a][b] == '#') {
            return false;
        }
        i ++;
        if (i == n1) {
            return true;
        }
        q.push({a, b});
    }
    return true;
}
int main() {
    cin >> n >> m >> n1;

    cin >> s;

    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            cin >> g[i][j];
        }
    }

    int res = 0;
    for (int i = 0; i < n; i ++)  {
        for (int j = 0; j < m; j ++) {
            // cout << g[i][j];
            if (g[i][j] =='.') {
                if (bfs(i, j)) {
                    res ++;
                }
            }
        }
        // cout << endl;
    }

    cout << res << endl;

}