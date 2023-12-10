#include<iostream>
#include<sstream>
#include<cstring>
using namespace std;

const int N = 200100, M =  500100;


int e[M], ne[M], h[N], w[M], idx;

int dist[N], q[N];

bool st[N];

int n, m;

void add (int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}


void spfa() {
    memset(dist, 0x3f, sizeof dist);

    int hh = 0, tt = 1;
    dist[1] = 0;
    q[0] = 1;

    while(hh != tt) {
        int t = q[hh ++];
        if (hh == N) hh = 0;

        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];

            if (dist[j] > dist[t] + 1) {
                dist[j] = dist[t] + 1;
                if (!st[j] ) {
                    st[j] = true;
                    q[tt ++] = j;
                    if (tt == N) tt =0;
                }
            }
        }
    }

    if (dist[n] == 2) cout << "POSSIBLE" << endl;
    else cout <<"IMPOSSIBLE" << endl;
}

int main() {

    cin >> n >> m;

    memset(h, -1, sizeof h);
    while (m --) {
        int a, b;
        cin >> a >> b ;
        add (a, b);
        add (b, a);
    }

    spfa();
    return 0;
}