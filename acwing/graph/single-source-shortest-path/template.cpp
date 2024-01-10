#include<iostream>
#include<cstring>
#include<queue>
using namespace std;


typedef pair<int,int> PII;

const int N = 1000, M = 1e5 + 10;


int h[N], ne[M], w[M], e[M], idx;
int dist[N];

int q[N];
bool st[N];

int n, m;
// a -> b
void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}
void spfa(int start) {
    memset(dist, 0x3f, sizeof dist );

    dist[start] = 0;
    st[start] = true;
    int hh = 0, tt = 1;
    while(hh != tt) {
        int t = q[hh ++];
        if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];

            if (!st[j]) {
                if (dist[j] > dist[t] + w[i] ) {
                    dist[j] = dist[t] + w[i];
                    st[j] = true;
                    q[tt ++] = j;
                    if (tt == N) tt = 0;
                }
            }
        }
    }
}

int dijkstra(int start) {
    memset(dist, 0x3f ,sizeof dist);

    dist[start] = 0;
    st[start] = true;

    for (int i = 0; i < n; i ++) {
        int t = -1;

        for (int j = 0; j < n; j ++) {
            if (!st[j] && (t == -1 || dist[j] < dist[t]) ) {
                t = j;
            }
        }
        st[t] = true;

        for (int j = 0; j < n; j ++) {
            if (dist[j] > dist[t] + w[j]) {
                dist[j] = dist[t] + w[j];
            }
        }
    }
}

void dijkstra2(int start) {
    memset(dist, 0x3f, sizeof dist);
    priority_queue<PII, vector<PII>, greater<PII>>  heap;

    dist[start] = 0;
    heap.push({0, start});


    while(heap.size()) {
        auto t = heap.top();
        int distance = t.first, node = t.second;
        heap.pop();
        
        if (st[node]) continue;
        st[node] = true;
        for (int i = h[node]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > distance + w[i]) {
                dist[j] = distance + w[i];
                heap.push({dist[j], j});
            }
        }

    }

}

int main() {


    return 0;


}