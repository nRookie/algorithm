#include<iostream>
#include<cstring>
using namespace std;


const int N = 10010;

int f[N], g[N];

int a[N];
int st[N];
int main() {
    int n;

    cin >> n;
    int m = 0;
    for (int i = 1; i <= n; i ++) {
        int x, y;
        cin >> x >> y ;
        st[x] = true;
        a[x] = y;
        m = max(m, x);
    }

    int res = 0;
    for (int i = 0; i <= m; i ++) {
        if (st[i]) {
            // cout << a[i] << " ";
            f[i] = 1;

            for (int j = 0; j < i; j ++) {
                if (st[j] && a[j] < a[i]) {
                    f[i] = max(f[i], f[j] + 1);
                }
            }
            res = max(res, f[i]);
        }
    }

    // cout << endl;
    cout << res << endl;


}