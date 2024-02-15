#include<iostream>
#include<cstring>
using namespace std;



typedef long long ll;

const int N = 1e6 + 10, M = 4 * N;

int h[N], ne[M], e[M], w[M], idx;

void add (int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}
int st[N];
ll dist[N];

int q[N];
void spfa() {
    memset(st, 0, sizeof st);
    memset(dist, 0x3f, sizeof dist);
    q[0] = 1; 
    dist[1] = 0;
    st[1] = true;
    int hh =0, tt = 1;
    while (hh != tt) {
        int t = q[hh ++];
        if (hh == N) hh = 0;
        st[t] = false;
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] >  dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if (!st[j]) {
                    st[j] = true;
                    q[tt ++] = j;
                    if (tt == N) tt =0;
                }
            }
        }
    }
}

int color[N];

void dfs(int u) {
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (st[j]) continue;
        st[j] = true;
        if ( (dist[j] & 1) == (dist[1]& 1 )) {
            color[j] = color[1];

        }  else {
            color[j] = !color[1];
        }
        dfs(j);
    }
}
int main() {
    int n;

    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i ++) {
        int a,b,c;
        cin >> a >> b >> c;
        add(a,b,c), add (b,a, c);
    }

    spfa();


    memset(st, 0, sizeof st);
    st[1] = true;

    dfs(1);

    // for (int i = 1; i <= n; i ++) {
    //     cout << dist[i] << " ";
    // }
    // cout << endl;

    for (int i = 1; i <= n; i ++) {
        cout <<color[i] << endl;
    }


}