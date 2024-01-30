#include<iostream>
#include<vector>
#include<cstring>
using namespace std;


const int N = 1e5 + 10, M = 3 * N + 10;

int h[N], e[M], w[M], ne[M], idx;

const int MAX = 1e6;
void add (int a, int b ) {
    e[idx] = b, ne[idx] = h[a] , h[a] = idx ++;
}


int st[N];
int path;
void dfs(int u) {
    if (path >= MAX) return;
    if(!st[u]) {
        st[u] = true;
        path ++;
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
    for (int i = 1; i <= n; i ++) {
        if (!st[i]) {
            dfs(i);
        }
    }
    cout << path << endl;
    return 0;
}