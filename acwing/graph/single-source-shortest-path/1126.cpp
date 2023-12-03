#include<iostream>
#include<cstring>
using namespace std;

const int N = 810, M = 3000, INF = 0x3f3f3f3f;



int n, p, m;


int id[N]; // 每个奶牛有牧场的编号

int ne[M], e[M], h[N], idx, w[M];
int dist[N], q[N];
bool st[N];


int add (int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;   
}


//所有奶牛到它的牧场的距离之和
int spfa(int start) {
    memset(dist, 0x3f, sizeof dist);
    dist[start] = 0;
    st[start] = true;
    
    int hh = 0, tt = 1;
    q[hh] = start;
    
    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        
        st[t] = false;
        
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if (!st[j]) {
                    st[j] = true;
                    q[tt ++] = j;
                    if (tt == N) tt = 0;
                }
            }
        }
    }
    
    int res = 0;
    for (int i = 0; i < n; i ++) {
        int j = id[i];
        if (dist[j] == INF)  return INF;
        res += dist[j];
    }
    return res;
}


int main () {
    memset(h, -1, sizeof h);
    
    
    cin >> n >>  p >> m;
    for (int i = 0; i < n; i ++) cin >> id[i];
    
    
    for (int i = 0; i < m; i ++) {
        int a, b, c;
        cin >> a >> b>> c;
        add (a, b, c), add (b, a, c);
        
    }
    
    int res = INF;
    
    // 循环牧场
    for (int i = 1; i <= p; i ++) res = min(res, spfa(i));
    
    cout << res << endl;
    
    return 0;
    
}