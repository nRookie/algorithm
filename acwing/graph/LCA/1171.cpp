#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;



typedef pair<int,int > PII;

const int N = 20010, M = 2 * N;

int q[N] , h[N], e[M], w[M], ne[M], idx;

int dist[N];
int p[N];

int depth[N];
int res[N];

int st[N];
int fa[N][17];

void add (int a, int b, int c) {
    e[idx] = b, w[idx] =c , ne[idx] = h[a], h[a] = idx ++;
}

int n, m ;

void bfs(int root) {
   
 
  memset(depth, 0x3f, sizeof depth);
  depth[0] = 0, depth[root] = 1;
  q[0] = root;
  int hh = 0, tt = 0;
    while (hh <= tt ) {
        int t = q[hh ++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (depth[j] > depth[t] + 1) {
                depth[j] = depth[t] + 1;
                dist[j] = dist[t] + w[i];
                fa[j][0] = t;
                q[++ tt] = j; 
                for (int k = 1; k <= 16 ; k ++) {
                    fa[j][k] = fa[fa[j][k - 1]][k - 1];
                }
            }
        }
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);

    for (int k = 16; k >= 0; k --) {
        if (depth[fa[a][k]] >= depth[b]) a = fa[a][k];
    }

    if (a == b) return a;

    for (int k = 16; k >= 0; k --) {
        if(fa[a][k] != fa[b][k]) {
            a = fa[a][k];
            b = fa[b][k];
        }
    }

    return fa[a][0];
}


int main() {
    scanf("%d%d", &n, &m);

    memset(h, -1, sizeof h);

    for (int i = 0; i < n - 1; i ++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add (a, b, c), add (b, a ,c );
    }
 
 
    bfs(1);

    for (int i = 0; i < m; i ++ ) {
        int a, b;
        scanf("%d%d", &a, &b);
        int t = lca(a, b);
        int ans = dist[a] + dist[b] - dist[t] * 2;
        printf("%d\n", ans);
    }
    return 0;
 
}
