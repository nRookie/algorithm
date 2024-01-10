#include<iostream>
#include<cstring>
using namespace std;


const int N = 1000;
typedef pair<int,int> PII;


PII fa[N][N];
int low[N][N], dfn[N][N];

int g[N][N];
int times = 0;

int dx[] = {-1, 0, 1 , 0};
int dy[] = {0, 1, 0, - 1};
int n, m;

int tarjan(int x, int y) {
    times++;
    dfn[x][y] = low[x][y] = times;
    int child = 0;
    
    for (int i = 0; i < 4; i ++) {
        int a = x + dx[i], b = y + dy[i];

        if (a < 0 || b < 0 || a >= n || b >= n) continue;

        if (g[a][b] == '#') {
            if (!dfn[a][b]) {
                child ++;
                fa[a][b] = {x, y};
                tarjan(a, b);

                if (fa[x][y] == make_pair(-1, -1) && child >= 2) {
                    // x is articulation point
                } 
                if (fa[x][y] != make_pair(-1, -1) && low[y] >= dfn[x]) {

                }

                if (low[y] > dfn[x]) {
                    // x->y is a bridge
                }
            } else if( make_pair(a, b) != fa[x][y] ) { // a,b is ancestor of x,y
                low[x][y] = min(low[x][y], low[a][b]);
            }
        }
    }
}

int main() {
 
    cin >> n >> m;

    for (int i = 0; i < n; i ++)
        for (int j = 0; j < m; j ++) {
            cin >> g[i][j];
            fa[i][j] = make_pair(-1,-1);
        }


    for (int x = 0; x < n; x ++)
        for (int y = 0; y < m; y ++) {
            if (!dfn[x][y])
                tarjan(x, y);
        }
}