#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;


typedef long long LL;


int p;


int qmi(int a, int k) {
    int res = 1;
    
    while (k) {
        if (k & 1) res = (LL)res * a % p;
        k >>= 1;
        a = (LL)a * a % p;
    }
    return res;
}


int C(int a, int b) {
    int res = 1;
    
    for (int i = 1, j = a; i <= b ; i ++, j -- ) {
        res = (LL) res * j % p;
        res = (LL) res * qmi(i, p - 2) % p;
    }
    return res;
}


int lucas(LL a, LL b) {
    if (a < p && b < p ) return C(a, b);
    return (LL) C(a % p, b % p) *  lucas(a / p, b / p) % p;
}


// a, 
// 
void solve() {
    int n, k;

    cin >> n >> k;
    // 123456
    // 000000
    // 000001
    // 
    k = min(30, k);
    cout <<  min((1 << k) - 1 ,  n)  + 1<< endl;
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}