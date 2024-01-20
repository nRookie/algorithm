#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;


const int N = 40010, M = N * 2;

int n,m ;

int h[N], e[M], ne[M], idx;


//
int depth[N], fa[N][16];


int q[N];

void add (int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}



// 预处理

void bfs(int root ) {
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0, depth[root] = 1;
    int hh = 0, tt = 0;
    q[0] = root ;
    
    while (hh <= tt) {
        int t = q[hh ++];
        for (int i = h[t] ; ~i; i = ne[i]) {
            int j = e[i];
            
            if (depth[j] > depth[t] + 1) {
                depth[j] = depth[t] + 1;
                
                q[ ++ tt] = j;
                fa[j][0] = t;
                for (int k = 1; k <= 15; k ++) {
                    fa[j][k] = fa[fa[j][k - 1]][k - 1];
                }
            }
        }
    }
}



int lca(int a, int b) {
    
    // 保证 a在b的下面
    if (depth[a] < depth[b]) swap(a, b);
    
    // 跳到同一层
    for (int k = 15; k >= 0; k --) 
        // 从a开始跳了2的k次方步之后，跳出了根节点 depth[fa[a][k]] 会返回0
        // 那么 0 >=  depth[b] 一定不成立，我们希望他不成立，
        if (depth[fa[a][k]]  >= depth[b]) {
            a = fa[a][k]; 
        }
        // a 或者b就是最近公共祖先
    if (a == b) return a ;
    
    for (int k = 15; k >= 0; k --) {
        // 哨兵的第二个好处
        // 如果a 跳出的话， 它是0， b跳出的时候也是 0， 不会满足要求。
        if(fa[a][k] != fa[b][k]) {
            a = fa[a][k];
            b = fa[b][k];
        }
    }
    
    return fa[a][0];
}
int main() {
    scanf("%d", &n);
    int root = 0;
    memset(h, -1, sizeof h);
    
    for (int i = 1; i <= n; i ++) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (b == -1) root = a;
        else add(a, b), add(b,a);
    }
    
    
    bfs(root);
    
    
    scanf("%d", &m);
    
    while (m --) {
        int a, b;
        scanf("%d%d", &a, &b);
        int p = lca(a, b);
        if (p == a) puts("1");
        else if (p == b) puts("2");
        else puts("0");
    }
    
    return 0;
}