#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;

const int N = 1010;
int n, m;
const int MOD = 998244353;

typedef long long LL;
typedef pair<int,int> PII;
PII fa[N][N];
int low[N][N], dfn[N][N];

char g[N][N];
int times = 0;

int dx[] = {-1, 0, 1 , 0};
int dy[] = {0, 1, 0, - 1};

vector<PII> adjacencyList[N][N]; 
long long qmi(long long a, long long k, long long p) {
    long long res = 1;

    while(k) {
        if (k & 1) res = (LL) res * a % p;
        k >>= 1;
        a = (LL)a * a % p;

    }
    return res;

}
 


void tarjan(int x, int y) {
    times++;
    dfn[x][y] = low[x][y] = times;
    int child = 0;
    
    for (int i = 0; i < 4; i ++) {
        int a = x + dx[i], b = y + dy[i];

        if (a < 0 || b < 0 || a >= n || b >= n || g[a][b] == '.') continue;

        if (!dfn[a][b]) {
            child ++;
            fa[a][b] = {x, y};
            adjacencyList[x][y].push_back(make_pair(a,b));
            tarjan(a, b);

            if (fa[x][y] == make_pair(-1, -1) && child >= 2) {
                // x is articulation point
                low[x][y] = min(low[x][y], low[a][b]);
            } 
            if (fa[x][y] != make_pair(-1, -1) && low[a][b] >= dfn[x][y]) {
                // x is articulation point
                low[x][y] = min(low[x][y], low[a][b]);
            }
            if (fa[x][y] == make_pair(a,b)) {
                // do not consider the parent node
            }

            if (low[a][b] > dfn[x][y]) {
                // x->y is a bridge
            }
        } else if( make_pair(a, b) != fa[x][y] ) { // a,b is ancestor of x,y
            low[x][y] = min(low[x][y], low[a][b]);
        }
    }
}

LL green = 0;
LL numBlocks = 0;
int main() {

    cin >> n >> m;
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < m; j ++) {
            cin >> g[i][j];
            if (g[i][j] == '#') {
                green ++;
            }
            fa[i][j] = make_pair(-1,-1);
        }

    for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++) {
        if (g[i][j] =='#' && dfn[i][j] == 0 )  {
                ++numBlocks;
                tarjan(i,j);
        }
    }


    LL res = 0;
    for (int x = 0; x < n; x ++)
    for (int y = 0; y < m; y ++) {
        if (g[x][y] == '#') {
            int c = 0;
            for (PII & t : adjacencyList[x][y]) {
                int a = t.first, b = t.second;

                c += (dfn[x][y] <= low[a][b]);
            }
            res += numBlocks -  1 + c + (fa[x][y] != make_pair(-1,-1));
        }
    }
 

    // long long modInvQ = qmi(red, MOD - 2, MOD);

    // Calculate R = (P * modInvQ) % MOD
    LL R = (res % MOD * qmi(green, MOD - 2, MOD) % MOD);

    // cout << numBlocks << " " << green << endl;
    // cout << res << endl; 
    std::cout << R << endl;
    return 0;
}
