#include<iostream>
#include<cstring>
#include<queue>
using namespace std;



const int N = 1010;

typedef long long ll;

typedef pair<ll,ll> PII;
#define x first
#define y second


ll d[N][N];
ll dc[N][N];
ll dt[N][N];
ll dist[N];
ll dist1[N];


ll n,a,b,c;

bool st[N];

void dijkstra(int start) {
    priority_queue<PII, vector<PII>, greater<PII> > heap;
    memset(dist, 0x3f, sizeof dist);
    heap.push({0, start});
    dist[start] = 0;

    while(heap.size()) {
        PII t = heap.top();
        heap.pop();


        if (st[t.y]) continue;
        st[t.y] = true;
        
        for (int i = 1; i <= n; i ++) {
            if (dist[i] > dist[t.y] + dc[t.y][i] ) {
                dist[i] = dist[t.y] + dc[t.y][i];
                heap.push({dist[i], i});
            }
        }

    }


}

void dijkstra2(int start) {
    priority_queue<PII, vector<PII>, greater<PII> > heap;
    memset(dist1, 0x3f, sizeof dist1);
    heap.push({0, start});
    dist1[start] = 0;

    while(heap.size()) {
        PII t = heap.top();
        heap.pop();
        if (st[t.y]) continue;
        st[t.y] = true;
        for (int i = 1; i <= n; i ++) {
            // 考虑坐火车方案
            if (dist1[i] > dist1[t.y] + dt[t.y][i] ) {
                dist1[i] = dist1[t.y] + dt[t.y][i];
                heap.push({dist1[i], i});
            }
        }

    }


}

void print()  {
    for (int i = 1;i <= n; i ++) {
        cout << dist[i] << " ";
    }

    cout << endl;

    cout << endl;
}
int main() {

    cin >> n >> a >> b >> c;

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            cin >> d[i][j];
            dc[i][j] = d[i][j] * a;
            dt[i][j] = d[i][j] * b + c; // d[i][j] * b + c; //
        }
    }

    
    dijkstra(1);
    memset(st, 0, sizeof st);
    dijkstra2(n);
    ll res = 0x3f3f3f3f3f3f3f3f;
    for (int i = 1; i <= n; i ++) {
        res = min(res, dist[i] + dist1[i] );
    }
    

    cout << res << endl;
    return 0;
}
// 4 8 5 13
// 0 6 2 15
// 6 0 3 5
// 2 3 0 13
// 15 5 13 0


// 168604826785
// 168608804787