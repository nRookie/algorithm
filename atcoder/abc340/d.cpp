#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

typedef long long ll;
const int N = 2 * 1e6 + 10, M =  4 * 1e6 + 10;


int h[N], e[M], ne[M], w[M], idx;


typedef pair<ll,ll> PII;
ll dist[N];
bool st[N];
void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}



void dijkstra(int start, ll dist[]) {
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
int main() {
    // N stage , 1- > n

    // sepnd Ai seconds to clear stage i,  -> play at stage i + 1
    // spend bi seconds to clear stage i, -> play at stage Xi.

    int n;
    memset(h, -1, sizeof h);
    cin >> n;
    for (int i = 1; i < n; i ++) {
        int a, b, x;
        cin >> a >> b >> x;
        add (i, i + 1, a);
        add (i, x, b);
    }
    dijkstra(1,  dist);
    cout << dist[n] << endl;
 
    return 0;
}