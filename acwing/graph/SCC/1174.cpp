#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

const int N = 10010, M = 5 * 1e4 + 10;

int h[N], ne[M], e[M], idx;

int timestamp;
int dfn[N], low[N], top, scc_cnt, Size[N], id[N] ;
int stk[N];
bool in_stk[N];
int n, m;
int dout[N];


void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a] , h[a] = idx ++;
}
void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u, in_stk[u] = true;

    for (int i = h[u]; ~i; i = ne[i] ) {
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
        scc_cnt++;
        do {
            y = stk[top --];
            Size[scc_cnt] ++;
            id[y] = scc_cnt;
            in_stk[y] = false;
        } while (y != u);
    }
}


int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);

    while(m --) {
        int a, b;
        cin >> a >> b ;
        add(a, b);
    }

    for (int i = 1; i <= n; i ++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    for (int i = 1; i <= n; i ++)
        for (int j = h[i]; ~j ; j = ne[j]) {
            int k = e[j];
            int a = id[i], b = id[k];
            if (a != b) dout[a] ++;
        }
        

    int zeros = 0, sum = 0;

    for (int i = 1; i <= scc_cnt; i ++) {
        if(!dout[i]) {
            zeros ++;
            sum = Size[i];
            if (zeros > 1) {
                sum = 0;
                break;
            } 
        }
    }
    cout << sum;
}