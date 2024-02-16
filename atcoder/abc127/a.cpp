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
    int a, b;
    cin >> a >> b;

    if (a <= 5) {
        cout << 0 << endl;
    } else if (a >= 6 && a <= 12) {
        cout << b / 2 << endl;
    } else {
        cout << b << endl;
    }
    return 0;
}