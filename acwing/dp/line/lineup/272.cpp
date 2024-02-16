#include<iostream>

#include<cstring>

using namespace std;


const int N = 3010;

int a[N], b[N];

int n;
int f[N][N];  // f[i][j] , 
int main() {
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i ++) {
        cin >> b[i];
    }

    int res = 0;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j++) {
            
            if (a[i] == b[j]) {
                f[i][j] = 1;
                for (int k = 1; k < j; k ++) {
                    f[i][j] = max(f[i][j], f[i - 1][k] + 1);
                }
                res = max(res, f[i][j]);
            }
            
        }
    }
    cout << res << endl;

    return 0;
}