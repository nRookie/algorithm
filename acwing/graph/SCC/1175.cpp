#include<iostream>
#include<cstring>
#include<algorithm>
#include<unordered_set> // 判重
using namespace std;


typedef long long LL;

const int N = 100010, M = 1000010 * 2;

int n, m, mod;

int dfn[N], low[N], timestamp;
int stk[N], top;

int h[N], hs[N], e[M], ne[M], idx ; // 由于要建立一个新图， 
bool in_stk[N];
int scc_cnt, Size[N], id[N];

int f[N],g[N];

void add(int *h, int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int tarjan(int u) {

    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u, in_stk[u] = true;

    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];

        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        } else if (in_stk[j]) {
            low[u] = min(low[u], dfn[j]);
        }

    }

    if (low[u] == dfn[u]) {
        int y;
        scc_cnt ++;
        do {
            y = stk[top--];
            in_stk[y] = false;
            id[y] = scc_cnt;
            Size[scc_cnt] ++;

        } while (y != u);
    }

}
int main() {

    memset(h, -1, sizeof h );
    memset(hs, -1, sizeof hs);


    cin >> n >> m >> mod;


    while (m -- ) {
        int a, b;
        scanf("%d%d",&a, &b);
        add(h, a, b);
    }

    for (int i = 1; i <= n; i ++) {
        if (!dfn[i])
            tarjan(i);
    }

    unordered_set<LL> S; // (u, v) -> u * 10 00000 + v

    for (int i = 1; i <= n; i ++)
        for (int j = h[i]; ~j; j = ne[j]) {
            int k = e[j];
            int a = id[i], b = id[k];
            LL hash = a * 1000000ll + b;
            if (a != b && !S.count(hash)) {
                add(hs, a, b);
                S.insert(hash);
            } 
        }

    for (int i = scc_cnt; i ; i --) {
        //   （还没有别更新过） -》起点
        if (!f[i]) {
            f[i] = Size[i];
            g[i] = 1;
        }

        // 当前这个点可以更新哪些点
        for (int j = hs[i]; ~j; j = ne[j]) {
            int k = e[j];
            // 可以被更新，找最大的
            if (f[k] < f[i] + Size[k]) {
                f[k] = f[i] + Size[k];
                g[k] = g[i];
            }
            else if (f[k] == f[i] + Size[k])
                g[k] = (g[k] + g[i]) % mod;
        }
    }

    int  maxf = 0, sum = 0;
    for (int i = 1; i <= scc_cnt; i ++)
        if (f[i] > maxf) {
            maxf = f[i];
            sum = g[i];
        }
        else if (f[i] == maxf) sum = (sum + g[i]) % mod;

    printf("%d\n", maxf);
    printf("%d\n", sum);
}