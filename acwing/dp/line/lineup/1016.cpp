#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;


const int N = 1010;

int a[N];
int f[N];
int main() {
    
    int n;
    cin >> n;
    
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    int res = 0;


    for (int i = 1; i <= n; i ++) {
        f[i] = a[i];

        for (int j = 1; j < i; j ++) {
            if (a[j] < a[i] ) {
                f[i] = max(f[i], f[j] + a[i]);
            }
        }
        res = max(res, f[i]);
    }
    cout << res << endl;
    
    
    return 0;
}