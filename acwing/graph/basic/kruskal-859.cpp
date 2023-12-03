#include<iostream>
#include<algorithm>
using namespace std;


const int N = 10000010;

int n, m;
int p[N];


struct Edge {
    int a, b, w;
    bool operator < (const Edge &W) const {
        return w < W.w;
    }
}edges[N];

int find (int x) {
    if (p[x] != x) p[x] = find(p[x]);
}

int main() {
    int n, m;
    scanf("%d%d",&n, &m);
    
    for (int i = 0; i < m; i ++) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        edges[i] = {a,b,w};
    }
    
    sort(edges, edges + m) ;
    
    int res = 0, cnt = 0;
    
    for (int i = 1; i <= n; i ++) p[i] = i;
    
    // 从小到大枚举所有边
    for (int i = 0; i < m; i ++) {
        int a = edges[i].a, b = edges[i].b, w = edges[i].w;
        //
        
        a = find(a), b = find(b);
        
        if (a != b) {
            p[a] = b;
            res += w;
            cnt ++;
        }
    }
    
    // 如果边小于 n - 1 说明这个图是不连通的
    
    if (cnt < n - 1) {
        puts("impossible");
    }
    else printf("%d\n", res);
    
    
}

