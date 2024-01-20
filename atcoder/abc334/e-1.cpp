#include<iostream>
#include<cstring>
#include<algorithm>
#include<unordered_set>
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

int low[N], dfn[N], timestamp;
int stk[N * N + 10], top;
bool in_stk[N * N + 10];
int id[N], Size[N];
int scc_cnt;

int getLoc(int x, int y) {
    return x * m + y;
}


// 0 1 2   3
// 4 5 6   7
// 8 9 10 11

void tarjan(int u) {
    dfn[u] = low[u] = ++ timestamp;
    in_stk[u] = true, stk[++top] = u;

    int x = u / m, y = u % m;
    for (int i = 0; i < 4; i ++) {
        int a = x + dx[i], b = y + dy[i];
        int j = getLoc(a, b);
        if ( a < 0 || b < 0 || a >= n || b >= m ) continue;
        if ( g[a][b] == '.') continue;
        // printf("%d %d %d %d %c\n", x, y, a, b, g[a][b]);
 
        if (!dfn[j]) {
            // printf("tarjan called with %d\n", j);
            tarjan(j);
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
            // cout <<"top is:" <<  top << " "<< y << endl;
 
        } while(y != u);
        // cout << scc_cnt << " " << Size[scc_cnt] << endl;
    }
}

int main() {
    cin >> n >> m;
    int red = 0;
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            cin >> g[i][j];
        }
    }

    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            int u = getLoc(i, j);
            // cout << i << " " << j << " " << "g[i][j] = " << g[i][j] << " " << u << " dfn[u] = " << dfn[u] <<  endl;
            if (g[i][j] == '#' && dfn[u] == 0) {
                // printf("tarjan called with %d %d \n", i, j);
                tarjan(u);
            }
        }
    }

    //cout << endl;

    // for (int i = 0; i <= n * m + 1; i ++) {
    //     printf("%d %d\n", dfn[i], low[i]);
    // }
    ll sum = 0;
    for (int x = 0; x < n; x ++) 
        for (int y = 0; y < m; y ++) 
            if (g[x][y] == '.') {
                red ++;
                int res = 0;
                unordered_set<int> s;
                for (int i = 0; i < 4; i ++) {
                    int a = x + dx[i], b = y + dy[i];

                    if ( a < 0 || b < 0 || a >= n || b >= m || g[a][b] == '.') continue;
                    int j = getLoc(a, b);
                    s.insert(id[j]);
                }
                sum += scc_cnt - (s.size() - 1);

        }


    // long long modInvQ = qmi(red, MOD - 2, MOD);

    // Calculate R = (P * modInvQ) % MOD
    // LL R = (res % MOD * qmi(red, MOD - 2, MOD) % MOD);
    ll R =  sum % MOD * qmi(red,MOD - 2, MOD) %MOD ;
    cout << R << endl;
    // cout << "scc_cnt:" <<scc_cnt << endl;
    // cout << sum << endl;
    // cout << red << endl;
    return 0;
}