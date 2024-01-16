#include<iostream>
#include<vector>
#include<queue>
#include<cstring>

using namespace std;


const int N = 25100, M = 51000 * 3, INF = 0x3f3f3f3f;


int dist[N];

bool st[N];

typedef pair<int,int> PII;


int h[N], e[M], ne[M], w[M], idx;
vector<int> block[N];

int bcnt;

int id[N];
queue<int> q;

int din[N];

void add (int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}

int n, m1, m2 , S;

void dfs(int u, int bid) {
    id[u] = bid;
    block[bid].push_back(u);
    
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!id[j]) {
            dfs(j, bid);
        }
    }
}


void dijiskra(int bid) {
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    
    for (auto u: block[bid]) {
        heap.push({dist[u], u});
    }
    
    while (heap.size()) {
        int t = heap.top().second;
        heap.pop();
        
        if (st[t]) continue;
        st[t] = true;
        for (int i = h[t]; ~i ; i = ne[i]) {
            int j = e[i];
            
            if (id[t] != id[j] && --din[id[j]] == 0 ) q.push(id[j]);
            
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if (id[j] == bid) {
                    heap.push({dist[j], j});
                }
            }
        }
    }
}
void toposort() {
    memset(dist, 0x3f, sizeof dist);
    dist[S] = 0;
    
    for (int i = 1; i <= bcnt; i ++) {
        if(!din[i]) {
            q.push(i);
        }
    }
    
    while(q.size()) {
        int t = q.front();
        q.pop();
        dijiskra(t);
    }
}

int main() {
    cin >> n >> m1 >> m2 >> S;
    
    memset(h, -1, sizeof h);
    
    while(m1 -- ) {
        int a, b, c;
        cin >> a >> b >> c ;
        add(a, b, c), add (b, a, c);
        
    }
    
    for (int i = 1; i <= n; i ++) {
        if (!id[i]) {
            bcnt ++;
            dfs(i, bcnt);
        }
    }
    
    while (m2 -- ) {
        int a , b, c;
        cin >> a >> b >> c ;
        
        add (a, b, c);
        din[id[b]] ++;
    }
    
    toposort();
    
    
    for (int i = 1; i <= n; i ++) {
        if (dist[i] > INF / 2) cout << "NO PATH" << endl;
        else cout << dist[i] << endl;
    }
}