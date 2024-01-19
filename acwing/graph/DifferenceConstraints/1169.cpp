#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>


const int N = 100000, M = 3 * N + 10;


int n, m;

int h[N], e[M], w[M], ne[M], idx;
int dist[N];
int q[N], cnt[N];
bool st[N];

void add (int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}

bool spfa() {

    int hh = 0, tt = 0;
    for (int i = 0; i <= n; i ++) {
        st[i] = true;
        q[tt ++] = i;
    }

    while(hh != tt) {
        int t = q[hh ++];
        if (hh == N) hh = 0;
        st[t] = false;
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];

            if (dist[j] < dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if (cnt[j] >= n) return true;
                if (!st[j]) {
                    st[j] = true;
                    q[tt ++] = j;
                    if (tt == N) tt = 0;
                }
            }
        }
    }

    return false;
}


int main() {
    scanf("%d%d",  &n, &m);

    memset(h, -1, sizeof h);

    while(m -- ) {
        int x, a, b;
        scanf("%d%d%d", &x,&a, &b);
        if (x == 1) add(b , a, 0), add (a, b, 0 );
        else if (x == 2) add (a, b, 1);
        else if (x == 3) add (b, a , 0);
        else if (x == 4) add (b, a, 1);
        else add (a, b , 0);
    }

    spfa();

    
}