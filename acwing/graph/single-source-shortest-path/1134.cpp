#include<iostream>
#include<cstring>
#include<queue>

using namespace std;


const int mod = 100003;


const int N = 1e5 + 10, M = 4 * 1e5 + 10;


int e[M], ne[M], h[N], idx;

int n, m;


int dist[N];
bool st[N];
int cnt[N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}


int bfs() {
    memset(dist, 0x3f, sizeof dist);
    queue<int> q; 

    q.push(1);
    cnt[1] = 1;
    dist[1] = 0;

    while(q.size()) {
        int t = q.front();
        q.pop();
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];

            if (dist[j] > dist[t] + 1) {
                dist[j] = dist[t] + 1;
                q.push(j);
                cnt[j] = cnt[t];

            } else if (dist[j] == dist[t] + 1) {
                cnt[j] = (cnt[j] + cnt[t] ) % mod;
            }
        }
    }
}


int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m --) {
        int a, b;
        cin >> a >> b ;
        add (a, b), add (b, a);
    }

    bfs();

    for (int i = 1; i <= n; i ++) {
        cout << cnt[i] << endl;
    }
}