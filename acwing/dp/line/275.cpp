#include<iostream>

#include<cstring>
#include<algorithm>

using namespace std;

const int N = 51;

int f[2 * N][N][N];

int g[N][N];

int main() {
    int n, m;

    cin >> n >> m;

    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= m; j ++)
            cin >> g[i][j];


    for (int k = 2; k <= n + m; k ++)
        for (int i1 = 1; i1 <= n; i1 ++)
            for (int i2 = 1; i2 <= n; i2++) {
                int j1 = k - i1, j2 = k - i2;
                if (j1 <= m && j2 <= m && j1 >= 1 && j2 >= 1) {
                    int &t = f[k][i1][i2];


                    int w = g[i1][j1];
                    if (i1 != i2) {
                        w += g[i2][j2];
                    }

                    t = max(t, f[k - 1][i1 - 1][i2 - 1]);
                    t = max(t, f[k - 1][i1 - 1][i2]);
                    t = max(t, f[k - 1][i1][i2 - 1]);
                    t = max(t, f[k - 1][i1][i2]);
                    t += w;
                }
            }
    
    cout << f[m + n][n][n] << endl;
    return 0;
}