#include<iostream>
#include<cstring>
#include<algorithm>
#include<unordered_set>
#include<vector>
using namespace std;


const int N = 1010;

typedef long long ll;
const int MOD = 998244353;

char g[N][N];

int n, m;

ll qmi(int a, int k, int p) {
   ll res = 1;

    while(k) {
        if (k & 1) res = (ll) res * a % p;
        k >>= 1;
        a = (ll)a * a % p;

    }
    return res;

}
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};

int low[N * N], dfn[N * N], timestamp;
int stk[N * N + 10], top;
bool in_stk[N * N + 10];
int id[N * N], Size[N * N];
int scc_cnt;

int getLoc(int x, int y) {
    return x * m + y;
}

vector<int> f(n * m + 10);
vector<vector<int>> son(n * m + 10);

void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++ timestamp;
    in_stk[u] = true, stk[++top] = u;
    f[u] = fa;
    int x = u / m, y = u % m;
    for (int i = 0; i < 4; i ++) {
        int a = x + dx[i], b = y + dy[i];
        int j = getLoc(a, b);
        if ( a < 0 || b < 0 || a >= n || b >= m ) continue;
        if ( g[a][b] == '.') continue;
 
        if (!dfn[j]) {
            son[u].push_back(j);
            tarjan(j, u);
            low[u] = min(low[u], low[j]);
        } else if (in_stk[j]) {
            low[u] = min(low[u], dfn[j]);
        }
    }

    if (dfn[u] == low[u]) {
        int y;
        scc_cnt ++;
        do {
            y = stk[top--];
            in_stk[y] = false;
            id[y] = scc_cnt;
            Size[scc_cnt] ++;
 
        } while(y != u);
    }
}

int main() {
    cin >> n >> m;
    int green = 0;
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            cin >> g[i][j];
        }
    }

    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            int u = getLoc(i, j);
            if (g[i][j] == '#' && dfn[u] == 0) {
                tarjan(u, u);
            }
        }
    }
    ll sum = 0;
    
    for (int x = 0; x < n; x ++) 
        for (int y = 0; y < m; y ++) 
            if (g[x][y] == '#') {
                green ++;
               int cnt = 0, u = getLoc(x, y);
                // printf("x:%d y: %d dfn: %d low: %d \n", x, y, dfn[u], low[u]);
                for (auto &v : son[u])
                {
                    cnt += (dfn[u] <= low[v]);
                }
                sum += scc_cnt - 1 + cnt + (f[u] != u);
            } 


    // long long modInvQ = qmi(red, MOD - 2, MOD);

    // Calculate R = (P * modInvQ) % MOD
    // LL R = (res % MOD * qmi(red, MOD - 2, MOD) % MOD);
    ll R =  sum % MOD * qmi(green,MOD - 2, MOD) %MOD ;
    cout << R << endl;
    // cout << "scc_cnt:" <<scc_cnt << endl;
    // cout << sum << endl;
    // cout << red << endl;
    return 0;
}