#include<iostream>
#include<sstream>
#include<cstring>
using namespace std;

const int N = 200100, M =  500100;


int e[M], ne[M], h[N], w[M], idx;

int dist[N], q[N];

bool st[N];

int n, m;

int color[N];

void add (int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}


void spfa(int start) {
    memset(dist, 0x3f, sizeof dist);

    int hh = 0, tt = 1;
    dist[start] = 0;
    q[0] = start;

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
}

int main() {

    cin >> n >> m;

    
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i ++) {
        int a, b;
        cin >> a >> b ;
        add (a, b);
        add (b, a);
    }
    spfa(1);
    while(m --) {
        int q1, q2;
        cin >> q1 >> q2;

        if (dist[q1]%2 == dist[q2]%2 ) cout << "Town" << endl;
        else cout << "Road" << endl;
    }
    return 0;
}