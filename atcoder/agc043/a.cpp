#include<iostream>
#include<cstring>
#include<deque>

using namespace std;

const int N = 110, INF = 0x3f3f3f3f;


#define x first
#define y second
long long dist[N][N];
char g[N][N];


typedef pair<int,int> PII;

int n, m;

int dx[] = {1, 0};
int dy[] = {0, 1};

// count the consecutive number of black blocks.

void bfs() {

    deque<PII> dq;

    dq.push_back({1,1});
    dist[1][1] = 0;
    if(g[1][1] == '#') dist[1][1] = 1;

    while(dq.size()) {
        PII t = dq.front();
        dq.pop_front();

        for (int i = 0; i < 2; i ++) {
            int x = t.x + dx[i], y = t.y + dy[i];

            if (x > n || y > m) {
                continue;
            }
            
            if (dist[x][y] == -1) {
                if (g[x][y] == '#') {
                    if(g[t.x][t.y] =='#') {
                        // if the current block is same as the former block, do not change the operation number, we can add it to the front.
                        dist[x][y] = dist[t.x][t.y];
                        dq.push_front({x, y});
                    }
                    else {
                        dist[x][y] = dist[t.x][t.y] + 1; // since we are counting the black blocks number,
                        dq.push_back({x, y});
                    }
                } else {
                    if(g[t.x][t.y] =='.') {
                        // if the current block is same as the former block, do not change the operation number, we can add it to the front.
                        dist[x][y] = dist[t.x][t.y];
                        dq.push_front({x, y});
                    }
                    else { // the color is not same, it might affect the following operation, we add it to the back.
                        dist[x][y] = dist[t.x][t.y];
                        dq.push_back({x, y});
                    }
                }
            }
        }
    }
}

void print() {
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            if (dist[i][j] == -1) cout << "x " ;
            else cout << dist[i][j] << " ";
        }

        cout << endl;
    }
}
int main() {
    
    cin >> n >> m;

    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= m; j ++) {
            cin >> g[i][j];
        }


    memset(dist, -1 ,sizeof dist);

    bfs();
    //print();
    cout << dist[n][m] << endl;
}