#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;



const int N = 1e6 + 10, M = 4 * N;

typedef pair<int,int> PII;
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
    string s;

    cin >> s;
    bool nnn = false;
    for (auto c : s) {
        if ( !nnn && c =='|') {
            nnn = true;
        } else if ( nnn && c == '|') {
            nnn = false;
        }
        if (nnn) {
        } else {

            if (c == '|') continue;
            cout << c;
        }
    }

    cout << endl;

    return 0;
}