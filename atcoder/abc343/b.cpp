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

    int n;
    cin >> n;
    vector<vector<int>> a(n + 1, vector<int> (n + 1, 0));

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            cin >> a[i][j];
        }
    }



    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            if (a[i][j] == 1) {
                cout << j << " ";
            }
        }
        cout << endl;
    }

    return 0;

}