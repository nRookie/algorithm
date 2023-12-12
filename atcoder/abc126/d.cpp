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
int v[N];

void add (int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c , h[a] = idx ++;
}


void dfs(int u) {
    for (int i = u; ~i; i = ne[i]) {
        int j = e[i];
        if (!st[j]) {
            cout << (w[i] & 1) << "\n";
            st[j] = true;
            dfs(j);
        }
    }
}
int main() {

    cin >> n;

    
    memset(h, -1, sizeof h);

    for (int i = 0; i < n - 1; i ++) {
        int a, b, c;
        cin >> a >> b >> c ;
        v[i] = b; 
        add (a, b, c);
        add (b, a, c);
    }
    dfs(1);
    
    return 0;
}