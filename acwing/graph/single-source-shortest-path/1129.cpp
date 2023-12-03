#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

const int N = 2510, M = 6200 * 2 + 10;


int n,m, S,T;
int h[N], e[M], w[M], ne[M], idx;
int dist[N], q[N];
bool st[N];

void add (int a , int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}


int spfa() {
    memset(dist , 0x3f, sizeof dist);
    
    dist[S] = 0;
    
    st[S] = true;
    
    int hh = 0, tt = 1;
    q[0] = S, st[S] = true;
    
    while (hh != tt) {
        int t = q[hh ++];
        if (hh == N) hh = 0;
        st[t] = false;
        
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if (!st[j]) {
                    q[tt ++] = j;
                    if (tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
    return -1;
    
}

int main() {
    cin >> n >> m >> S >> T;
    
    
    memset(h, -1, sizeof h);
    
    for (int i = 0; i < m; i ++) {
        int a, b, c;
        cin >> a>> b >> c;
        add (a, b, c), add (b,a, c);
    }
    
    
    spfa();
    
    cout << dist[T] << endl;
    
    return 0;
    
}