#include <iostream>
#include <sstream>
#include <cstring>
using namespace std;

const int N = 3000,  INF = 0x3f3f3f3f;

// dp[i][j]  length is j, end with i, the valid count
int dp[N][N];

int dist[N][N];

int n, x, y;
int res[N];


void print() {
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            if (dist[i][j] == INF) cout << "x " ;
            else cout << dist[i][j] << " ";
        }

        cout << endl;
    }
}
int main()
{

    cin >> n >> x >> y;
    memset(dist, 0x3f, sizeof dist);

    for (int i = 1; i <= n; i++)
    {
        dist[i][i] = 0;
    }

    for (int i = 1; i < n; i++)
    {
        dist[i][i + 1] = 1;
        dist[i + 1][i] = 1;
    }
    dist[x][y] = 1;
    dist[y][x] = 1;

    // print();
    // cout << endl;

    for (int i = n - 1; i >= 1; i --)
        for (int j = i + 1; j <= n; j ++) {
                dist[i][j] = min(dist[i][j], min(dist[i][j - 1], dist[i + 1][j] ) + 1);
                // dist[j][i] = dist[i][j]; // min(dist[j][i], min(dist[j - 1][i], dist[j][i + 1] ) )+ 1;
            }

    // print();
    // cout << endl;


    for (int i = 1; i <= n; i ++)
        for (int j = i + 1; j <= n; j ++) {
                dist[i][j] = min(dist[i][j], dist[i][x] + dist[x][y] + dist[y][j]);
                // dist[j][i] = dist[i][j];
        }


    // print();
    // cout << endl;

    for (int i = 1; i <= n; i ++)
        for (int j = i + 1; j <= n; j ++) {
            if (dist[i][j] != 0 || dist[i][j] != INF) {
                res[dist[i][j]] ++;
            }
        }
    // cout << endl;
    for (int k = 1; k < n; k++)
    {
        cout << res[k] << endl;
    }
    return 0;
}




// 7 2 4 
//   1 2 3 4 5 6 7 
// 1 0 1 2 2 3 4 5 
// 2 1 0 1 1 2 3 4 
// 3 2 1 0 1 2 3 4 
// 4 2 1 1 0 1 2 3 
// 5 3 2 2 1 0 1 2 
// 6 4 3 3 2 1 0 1 
// 7 5 4 4 3 2 1 0 





// 7 2 4
//   1 2 3 4 5 6 7
// 1 0 1 2 3 4 5 6 
// 2 1 0 1 2 3 4 5 
// 3 2 1 0 1 2 3 4 
// 4 3 2 1 0 1 2 3 
// 5 4 3 2 1 0 1 2 
// 6 5 4 3 2 1 0 1 
// 7 6 5 4 3 2 1 0


// dist[i][j] = dist[i][j - 1] + 1



// 7 2 4 
//   1 2 3 4 5 6 7 
// 1 0 1 2 2 3 4 5 
// 2 1 0 1 1 2 3 4 
// 3 2 1 0 1 2 3 4 
// 4 2 1 1 0 1 2 3 
// 5 3 2 2 1 0 1 2 
// 6 4 3 3 2 1 0 1 
// 7 5 4 4 3 2 1 0 



