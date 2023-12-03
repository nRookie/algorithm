#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;


int g[501][501];

const int INF = 0x3f3f3f3f;

int n, m;

int dist[501];
int st[501];


void prim() {
    int res = 0;
    for (int i = 0; i < n ; i ++) {
        int t = -1;
        
        for (int j = 1; j <= n; j ++) {
            if (!st[j] && (t == -1 || dist[t] > dist[j])) {
               // printf("dist[t]: %d  dist[j]: %d\n", dist[t], dist[j]);
                t = j;
            }
        }
    
        //printf("%d current dist: %d \n",t, dist[t]);
        if (i && dist[t] == INF) {
            cout << "impossible";
            return ;
        }
        if (i) res += dist[t];
        
        for (int j = 1; j <= n; j ++) {
            dist[j] = min(dist[j], g[t][j]);
        }
        st[t] = true;
        
    }
    
    cout << res << endl;
    return;
}

int main() {
    
    
    cin >> n >> m;
    
    
    memset(g, 0x3f, sizeof g);
    memset(dist, 0x3f, sizeof dist);
    
    while(m --) {
        int a,b,c;
        cin >> a >> b>> c;
        
        g[a][b] = g[b][a] = min(g[a][b], c);
    }
    
    prim();
    
}