#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>

using namespace std;


const int N = 50010, M = 200010, INF = 0x3f3f3f3f;


int n, m;

int source[6];

int h[N], e[M], ne[M], idx, w[M];


int st[N];
int q[N], dist[6][N];

void add (int a, int b , int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c , h[a] = idx ++;
}



typedef pair<int,int> PII;
void spfa(int start, int dist[]) {
    memset(dist, 0x3f, N * 4);
    dist[start] = 0;
    
    int hh = 0, tt = 1;
    q[0] = start;
    st[start] = true;
    while (hh != tt ) {
        int t = q[hh ++];
        if (hh == N) hh = 0;
        st[t] = false;
        
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if (!st[j]) {
                    st[j] = true;
                    q[tt++] = j;
                    if (tt == N) tt = 0;
                }
            }
        }
    }
}

void dijkstra(int start, int dist[]) {
    memset(dist, 0x3f, N * 4);
    memset(st, 0, sizeof st);
    dist[start] = 0;
    
    priority_queue<PII, vector<PII>, greater<PII>> q;
    
    q.push({0, start});
    
    while(q.size()) {
        auto t = q.top().second;
        q.pop();
        if (st[t]) continue;
        st[t] = true;
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                q.push({dist[j], j});
            }
        }
    }
}


int dfs(int u, int start, int distance) {
    if (u == 6) return distance;
    
    int res = INF;
    
    for (int i = 1; i <= 5; i ++) {
        if (!st[i]) {
            int next = source[i];
            st[i] = true;
            res = min(res, dfs(u + 1, i , distance + dist[start][next]));
            st[i] = false;
        }
    }
    return res;
}
int main() {
    scanf("%d%d", &n, &m);
    
    source[0] = 1;
    for (int i = 1; i <= 5; i ++) scanf("%d", &source[i]);
    
    memset(h, -1, sizeof h);
        
    
    while (m --) {
        int a, b, c ;
        
        scanf("%d%d%d", &a, &b, &c);
        add(a,b,c) , add (b,a,c);
    }
    
    for (int i = 0; i < 6; i ++ ) dijkstra(source[i], dist[i]);
    
    memset(st, 0, sizeof st);
    printf("%d\n", dfs(1, 0, 0));
    
    return 0;
    
}