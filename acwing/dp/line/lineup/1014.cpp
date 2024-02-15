#include<iostream>
#include<cstring>
using namespace std;

const int N = 1100;

int h[N];

int main() {

    int n; 
    cin >> n;
    
    for (int i = 1; i <= n; i ++) {
        cin >> h[i];
    }
    int res = 0;
    
    int f[N];

    for (int i = 1; i <= n; i ++) {
        f[i] = 1;
        for (int j = 1; j < i; j ++) {
            if (h[j] > h[i]) {
                f[i] = max(f[i], f[j] + 1);
            }
        }
        res = max(res, f[i]);
    }
    
    for (int i = n; i >= 1; i --) {
        f[i] = 1;
        for (int j = n; j > i; j --) {
            if (h[j] > h[i]) {
                f[i] = max(f[i], f[j] + 1);
            }
        }
        res = max(res, f[i]);
    }


    cout << res << endl;
}