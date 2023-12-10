#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n,  s, k;


int main() {
    
    cin >> n >> s >> k;
    long long res = 0;
    for (int i = 1; i <= n; i ++) {
        int p,q ;
        cin >> p >> q;
        res += p * q;
    }

    if (res < s) {
        res += k;
    }
    cout << res << endl;
}