#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

 

 const int N = 20, M = 1 << N;



int n;
int w[N][N]; // 距离

int f[M][N];



int main() {
    cin >> n;

    for (int i = 0; i < n; i ++)
        for (int j = 0; j < n; j ++)
            cin >> w[i][j];

    memset(f, 0x3f, sizeof f);
    f[1][0] = 0;

    for (int i = 0; i < 1 << n; i ++)
        for (int j = 0; j < n; j ++)
            if (i >> j & 1) {
                for (int k = 0; k < n; k ++) 
                    if (i - ( 1 << j)  >> k & 1)   // i 除去j这个点 一定要包含 k这个点
                        f[i][j] = min(f[i][j], f[i - (1 << j)][k] + w[k][j]);
            }
    

    cout << f[(1<< n) - 1][n - 1] << endl;
}