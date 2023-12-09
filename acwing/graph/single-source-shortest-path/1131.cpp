#include<iostream>
#include<cstring>
#include<algorithm>
#include<deque>
#include<set>
using namespace std;

#define x first
#define y second

typedef pair<int, int> PII;


// 这里M不是邻接表的大小
const int N = 11, M =  N * N , E = 400, P = 1 << 10, INF = 0x3f3f3f3f;

int n, m, p, k;

int h[M], e[E], ne[E], w[E], idx;


//把二维坐标变成1位， 存哪个格子上有钥匙
int g[N][N], key[M];


// 到每个点，每种状态的一个距离。
int dist[M][P];

// 判重用
bool st[M][P];


set<PII> edges; // 当前哪个边已经被加上了


void add (int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c,  h[a] = idx ++;
}


void build() {
    int dx[4] = {-1, 0 , 1, 0};
    int dy[4] = {0, 1, 0, -1};
    
    // 枚举所有边
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= m; j ++)
            for (int u = 0; u < 4; u ++) {
                //枚举上下左右四个方向
                
                int x = i + dx[u], y = j + dy[u];
                
                if (x == 0 || x > n || y == 0 || y > m) continue;
                int a = g[i][j], b = g[x][y];
                
                // 判断这条边是不是出现过
                if (edges.count({a, b}) == 0) add(a, b, 0); // 0表示不是门，可以直接通过。
            }
    
}

int bfs() {
    
    memset(dist, 0x3f, sizeof dist);
    deque<PII> q;
    
    
    // 一开始没有钥匙,状态是0
    // x 是对应的坐标
    dist[1][0] = 0;
    
    q.push_back({1, 0});
    
    
    while (q.size()) {
        PII t = q.front();
        q.pop_front();
        
        // 和狄杰斯特拉的判重数组是一样的
        if (st[t.x][t.y]) continue;
        st[t.x][t.y] = true;
        
        if (t.x == n * m) return dist[t.x][t.y];
        
        // 计算两种边
        
        //如果有钥匙的
        if (key[t.x]) {
            // 拿上钥匙
            int state = t.y | key[t.x];
            
            if (dist[t.x][state] > dist[t.x][t.y]) {
                dist[t.x][state] = dist[t.x][t.y];
                q.push_front({t.x, state}); // 把当前这个点加到队头， 因为边权是0
            }
        }
        
        
        // 枚举一下正常的边
        for (int i = h[t.x]; ~i; i = ne[i]) {
            int j = e[i];
            
            // 没有门的话可以直接过
            // 有门但是没有钥匙不可以过
            if (w[i] && !(t.y >> w[i] - 1 & 1)) continue; // 这里所有钥匙的编号是减了1的
            // 检查有没有对应的钥匙，检查t.y的第 w[i] - 1位就可以了。
            if (dist[j][t.y] > dist[t.x][t.y] + 1) {
                dist[j][t.y] = dist[t.x][t.y] + 1;
                q.push_back({j, t.y}); // 因为边权是1 所以加到队尾取
            }
        }
    }
    
    return -1;
    
}


int main() {
    
    cin >> n >> m >> p >> k;

    // 给所有点编号
    for (int i = 1, t = 1; i <= n; i ++) 
        for (int j = 1; j <= m; j ++)
            g[i][j] = t ++;
    
    memset(h, -1, sizeof h);
    
    while (k --) {
        int x1, y1, x2, y2, c ;
        cin >> x1 >> y1 >> x2 >> y2 >> c;
        int a = g[x1][y1], b = g[x2][y2];
        // 表示边已经被用过了
        edges.insert({a, b}) , edges.insert({b, a});
        
        // 如果是一堵墙的就不用管他了。
        if (c) add(a, b, c), add (b, a, c);
    }
    
    // 把剩余的边建立起来
    build();
    
    
    // 把钥匙读进来
    
    int s;
    cin >> s ;
    
    while(s --) {
        int x,y, id;
        cin >> x >> y >> id;
        // x y 的编号是g[x][y]
        // 这里编号应该是从1开始的，但是为了节省空间，我门偏移了1
        // 因为是状态序列，所以要用 |=
        key[g[x][y]] |= 1 << id - 1;
    }
    cout << bfs() << endl;
    
    return 0;
}