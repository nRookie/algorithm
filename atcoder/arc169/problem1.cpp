#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>


using namespace std;

const int N = 250010;
long long   a[N], p[N];
int n;

long long depth[N];
long long b[N];
int main() {

    cin >> n;

    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    for (int i = 2; i <= n; i ++) {
        cin >> p[i];
    }

    for (int i = 2; i <=n; i ++) {
        depth[i] = depth[p[i]] + 1;
    }

    for (int i = 1; i <= n; i ++) {
        b[depth[i]] += a[i];
    }

    // Find the largest j for which B_j is non-zero
    int k = -1;

    for (int j = n - 1; j >= 0; j -- ) {
        if (b[j]) {
            k = j;
            break;
        }
    }
    if (k == -1) {
        cout << "0\n"; 
    } else {
        cout << (b[k] > 0 ? "+" :"-") << "\n";
    }
    return 0;
}