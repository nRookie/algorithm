#include<iostream>
#include<vector>
#include<cstring>
using namespace std;


const int N = 110, M = N * N + 10;

int h[N], e[M], w[M], ne[M], idx;

void add (int a, int b ) {
    e[idx] = b, ne[idx] = h[a] , h[a] = idx ++;
}

int scc;

int st[N];
void dfs(int u) {
    if(!st[u]) {
        st[u] = true;
        for (int i = h[u]; ~i; i = ne[i]) {
            int j = e[i];
            dfs(j);
        }
    }
}

int n, m;
int main() {
    cin >> n >> m;

    memset(h, -1 , sizeof h);

    while (m --) {
        int a, b;
        cin >> a >> b;
        add (a, b);
        add (b, a);
    }
    scc = 0;
    for (int i = 1; i <= n; i ++) {
        if (!st[i]) {
            scc ++;
            dfs(i);

        }
    }
    cout << scc << endl;
    return 0;
}