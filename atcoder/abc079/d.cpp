#include<iostream>
#include<cstring>
using namespace std;


const int N = 1010;


int dist[11][11];
int g[N][N];
int n, m;
int main() {
    cin >> n >> m;


    for (int i = 0; i <= 9; i++)   
        for(int j = 0; j <= 9; j++)
            cin >> dist[i][j];


    for (int k = 0; k <= 9; k ++ ) 
        for (int i = 0; i <= 9; i ++)
            for (int j = 0; j <= 9; j++) 
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    int res = 0;
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < m; j++) {
            int a;
            cin >> a ;
            if (a != -1) {
                res += dist[a][1];
            }
        }


    cout << res <<  endl;
    return 0;
}