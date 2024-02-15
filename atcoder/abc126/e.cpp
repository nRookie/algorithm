#include<iostream>
#include<cstring>
using namespace std;


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


// N cards, face down  1, or 2.


// Ai -> integer written on the i-th card.

// A1,A2,A3, ..., AN correctly

// each i = 1,2,..., M, the value A



// Axi + Ayi + Zi = even number

// choose one card and know the integer Ai written on it. the cost of using this magic is 1.

// A1, A2, ..., AN ?


// 3 1
// 1 2 1

// 2


const int N = 1e6 + 10, M = 4 * N;

int h[N], ne[M], e[M], w[M], idx;

void add (int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}
int st[N];
ll dist[N];

int q[N];


void dfs(int u) {
    if (st[u]) return;
    st[u] = true;

    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        dfs(j);
    }
}
int main() {
    int n, m;

    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m -- ) {
        int a, b, c;
        cin >> a >> b>> c;
        add(a,b ,c ), add (b,a,c);
    }

    int cnt = 0;
    for (int i = 1; i <= n; i ++) {
        if (!st[i]) {
            dfs(i);
            cnt ++;
        }
    }

    cout << cnt << endl;
}