#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;


const int N = 2 * 1e4 + 10, M = 2 * 1e5 + 10;


int h[N], ne[M], e[M], idx;
int depth[N];
int fa[N][17];
int q[N];

const int MOD = 998244353;

void add (int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}


void bfs(int root) {
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0, depth[root] = 1;
    int hh = 0, tt = 0;
    q[0] = root;
    while(hh <= tt) {
        int t = q[hh ++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (depth[j] > depth[t] + 1) {
                depth[j] = depth[t] + 1;
                fa[j][0] = t;
                for (int k = 1; k <= 16; k ++) {
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

    for (int k = 16; k >= 0; k --) {
        if (fa[a][k] != fa[b][k]) {
            a = fa[a][k];
            b = fa[a][k];
        }
    }

    return fa[a][0];
}


int dist(int a, int b ) {
    int c = lca(a, b);
    return depth[a] + depth[b] - depth[c] * 2;
}

int child (int c, int a) {
    if (c == a) return -1;
    return up(a, depth[a] - depth[c] - 1);
}
int n, m, K;
int main() {

    cin >> n >> m >> K;

    memset(h, -1, sizeof h);

    for (int i = 0; i < n; i ++) {
        int a ;
        cin >> a ;
        add (a, i + 1), add (i + 1, a);
    }

    vector<bool> ordered(n);

    for (int i = 0; i < m; i ++) {
        int a, b;
        cin >> a >> b ;
        int c = lca(a, b);
        int ca = child(c, a);
        int cb = child(c, b);
        up[a] ++; up[c] --;
        down[b] ++; down[c] --;
        up2[a] ++; down[c] -- ;
        if (ca != -1) up2[a] ++, up2[ca] --;
        if (cb != -1) down2[b] ++, down2[cb] --;
        if(ca != -1 && cb != -1) {
            if (ordered[c] )
        }
    }


}