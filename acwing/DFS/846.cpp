#include<iostream>
#include<cstring>
using namespace std;


const int N = 100010, M = 2 *N + 10;
int h[N], ne[M],e[M], idx;

int Size[N];
int ans = N;
int st[N];

void add (int a, int b) {
    e[idx] = b, ne[idx] = h[a] , h[a] = idx++;
}

int n, m;
void dfs(int u) {
    
    Size[u] = 1;
    st[u] = true;
    int max_part = 1;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!st[j]) {
            dfs(j);
            max_part = max(max_part, Size[j]);
            Size[u] += Size[j];
        }
    }

    max_part = max(max_part, n - Size[u]);

    if (ans > max_part) {
        ans = max_part;
    }
}

int main() {
    memset(h, -1, sizeof h);

    cin >> n;
    m = n - 1;
    while (m --) {
        int a, b;
        cin >> a >> b ;
        add (a,b), add (b,a);
    }

    dfs(1);

    cout << ans << endl;

}