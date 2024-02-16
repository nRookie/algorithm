#include<iostream>

using namespace std;



const int N = 1e6 + 10, M = 4 * N;

int h[N], ne[M], e[M], w[M], idx;

void add (int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}


typedef long long ll;
ll exgcd(ll a, ll b, ll & x, ll&  y) {
    
        if (b == 0) {
            x = 1;
            return a;
        }
        ll d = exgcd(b, a % b, y , x);
        y -= a/b * x;  
        
        return d;
}



int main() {
    // total weight,  beginning of year  xi, gram,  
    // xi + 1 = rxi - D   i >= 2000
    // r, D, and 2


    int r, d, x;

    cin >> r >> d>> x;

    for (int i = 1; i <= 10; i ++) {
        x = r * x - d;
        cout << x << endl;
    }
    return 0;
}