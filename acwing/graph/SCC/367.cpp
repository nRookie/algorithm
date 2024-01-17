#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 110, M = 10010;


int n;

int h[N], e[M], ne[M], idx;


int dfn[N], low[N], timestamp;

int stk[N], top;
int id[N], scc_cnt;
int din[N], dout[N];

bool in_stk[N];

void add (int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}


void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u, in_stk[u] = true;
    // 0 1
    // 1 2
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];

        if (!dfn[j]) {
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
        } while ( y != u);
    }
}
int main() {
    cin >> n;

    memset(h, -1, sizeof h);

    for (int i = 1; i <= n; i ++) {
        int t;
        while (cin >> t, t) add (i, t);
    }

    for (int i = 1; i <= n; i ++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }



    for (int i = 1; i <= n; i ++)
        for (int j = h[i]; ~j; j = ne[j]) {
            int k = e[j];
            int a = id[i], b = id[k];
            if (a != b) {
                din[b] ++;
                dout[a] ++;
            }
        }

    int p = 0, q = 0;

    for (int i = 1; i <= scc_cnt; i ++ ) {
        if (!din[i]) p ++;
        if (!dout[i]) q ++;
    }

    // for (int i = 1; i <= n; i ++) {
    //     printf("%d dfn: %d low: %d \n", i, dfn[i], low[i]);
    // }    
    printf("%d\n", p);


    if (scc_cnt == 1) puts("0");
    else printf("%d\n", max(p, q));
}