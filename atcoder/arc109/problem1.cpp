#include<iostream>
#include<sstream>
#include<cstring>
using namespace std;

const int N = 1000, M =  100000;


int e[M], ne[M], h[N], w[M], idx;

int dist[N], q[N];

bool st[N];

int a, b, y, x;

void add (int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}

void spfa() {
    memset(dist, 0x3f, sizeof dist);
    dist[a] = 0;
    int hh = 0, tt = 1;
    q[0] = a;

    while(hh != tt) {
        int t = q[hh ++];
        if (hh == N) hh = 0;
        st[t] = false;
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if (!st[j]) {
                    q[tt ++] = j;
                    if (tt == N) t = 0;
                    st[j] = true;
                }
            }
        }
    }

}

int main() {

    cin >> a >> b >> x >> y;
    b += 100;
    memset(h , -1, sizeof h);

    for (int i = 1; i < 100; i ++) {
        add (i, i + 1, y);
        add (i + 1, i, y);
    }

    for (int i = 101; i < 200; i ++) {
        add (i, i + 1, y);
        add (i + 1, i, y);
    }

    for (int i = 1; i <= 100; i ++) {
        add (i, i + 100, x);
        add (i + 100, i, x);
    }

    for (int i = 1; i <= 99; i ++) {
        add (i + 1, i + 100, x);
        add (i + 100, i + 1, x);
    }
    spfa();

    cout << dist[b] << endl;
    return 0;
}