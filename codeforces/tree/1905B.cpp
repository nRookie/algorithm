#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;



const int N = 2 * 1e6 + 10, M = 4 * N;

typedef pair<int,int> PII;
int h[N], ne[M], e[M], w[M], idx;

void add (int a, int b) {
    e[idx] = b, ne[idx] = h[a],  h[a] = idx ++;
}


typedef long long ll;
ll exgcd(ll a, ll b, ll & x, ll&  y) {
    
        if (b == 0) {
            x = 1;
            return a;
        }
        ll d = exgcd(b, a % b, y , x);
        y -= a/b * x;  
        
        return d;
}



// 1. choose two vertices of the tree u and v.
// 2. compress all the vertices on the path from u to v into one vertex.
// in other words, all the vertices on path from u to v will be erased from the tree,
// a new vertex w will be created. Then every vertex s that had an edge to some vertex on the path from u to v will have
// an edge to the vertex w.


int stk[N], top, timestamp; 
bool in_stk[N];
int dfn[N], low[N], id[N];
int scc_cnt;
int degree[N];

void tarjan(int u) {
    low[u] = dfn[u] = ++timestamp;
    stk[++top] = u, in_stk[u] = true;

    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];

        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        } else if (in_stk[j]) {
            low[u] = min(dfn[j], low[u]);
        }
    }

    if (dfn[u] == low[u]) {
        int y;
        scc_cnt ++;
        do {
            y = stk[top--];
            in_stk[y] = false;
            id[y] = scc_cnt;
        }while(y != u);
    }
}
void solve() {
    int n;
    cin >> n;
    for (int i = 1; i < n; i ++) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
        degree[b]++;
        degree[a]++;
    }

    int leaf = 0;
    for (int i = 1; i <= n; i ++) {
        // cout << degree[i] << endl;
        if (degree[i] == 1) {
            leaf ++;
        }
        degree[i] = 0;
    }

    cout << (leaf + 1) / 2 << endl;
 
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}