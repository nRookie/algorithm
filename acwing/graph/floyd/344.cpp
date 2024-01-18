#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 110, INF = 0x3f3f3f3f;


int n, m;

int d[N][N], g[N][N];


int p[N][N]; // 每一个点是从哪个点转移过来的


int path[N], cnt; // 当前的一个最小环的方案是什么， cnt是里面点的数量。



void get_path(int i, int j) {
    if (p[i][j] == 0) {
        return;
    }

    int k = p[i][j];
    get_path(i, k);
    path[cnt ++] = k;
    get_path(k, j);
}

int main() {
    cin >> n >> m;

    memset(g, 0x3f, sizeof g);

    for (int  i = 1; i <= n; i ++) g[i][i] = 0;

 

    while (m --) {
        int a, b, c ;
        cin >> a >> b >> c ;
        g[a][b] = g[b][a] = min(g[a][b], c);
    }


    memcpy(d,g, sizeof d);
        int res = INF;

    for (int k = 1; k <= n; k ++) {
         
         // 枚举最小环, k 是环上最大的点
        for (int i = 1; i < k; i ++) {
            // 因为是无向图， i 和j是上下翻转， 没有必要
            for (int j = i + 1; j < k; j ++) {
                //当前方案的最小值，先从i到j， 从j到k
                if ((long long) d[i][j] + g[j][k] + g[k][i] < res) {
                    res =  d[i][j] + g[j][k] + g[k][i];
                    cnt = 0;
                    path[cnt ++] = k;
                    path[cnt ++] = i;
                    get_path(i, j);
                    path[cnt ++] = j;
                }
            }
        }
        for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= n; j ++) {
            if (d[i][j] > d[i][k] + d[k][j]) {
                d[i][j] = d[i][k] + d[k][j];
                p[i][j] = k; 
            }
        }
        
    }


    if (res == INF) puts("No solution.");
    else {
        for (int i  = 0; i < cnt; i ++) cout << path[i] << ' ';
        cout << endl;
    }
}
