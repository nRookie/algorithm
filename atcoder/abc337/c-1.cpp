#include<iostream>
#include<cstring>
using namespace std;



const int N = 3* 1e5 + 10, M = N + 10;
int h[N], ne[M], e[M], idx;


void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dfs(int u) {
    if (u) cout << u << " ";
    for (int i = h[u] ; ~i; i = ne[i]) {
        int j = e[i];
        dfs(j);
    }
}
int main() {
    int n;
    memset(h, -1,sizeof h);
    cin >> n;

    for (int i = 1; i <= n; i ++) {
        int a;
        cin >> a;
        if (a == -1) {
            add(0, i);
        } else {
            add(a, i);
        }
    }

    dfs(0);

    return 0;
}