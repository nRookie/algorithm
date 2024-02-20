#include<iostream>
#include<vector>
#include<set>
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



// a, 
// 
void solve() {
    int n, m;
    char c;
    cin >> n >> m;
    cin >> c;

    vector<vector<char>> g(n + 1, vector<char> (m + 1));

    set<char> deputies;

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            cin >> g[i][j];
        }
    }


    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            if (g[i][j] == c) {
                int dx[] = {0, 1, 0, -1};
                int dy[] = {1, 0, -1, 0};

                for (int i1 = 0; i1 < 4; i1 ++) {
                    int a = i + dx[i1], b = j + dy[i1];


                    if (a < 1 || b < 1 || a > n  || b > m) {
                        continue;
                    }

                    if (g[a][b] != c && g[a][b] !='.') {
                        deputies.insert(g[a][b]);
                    }
                }
            }
        }
    }
    int x = 0;
    if (deputies.find('.') != deputies.end()) {
        x --;
    }


    cout << deputies.size() + x << endl; 


 
}


int main() {
    solve();
}