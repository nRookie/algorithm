#include<iostream>
#include<cstring>
#include<queue>
#include<unordered_map>
#include<set>
using namespace std;

const int N = 1010;
char g[N][N];
bool st[N][N];
int n, m;
const int MOD = 998244353;

typedef long long LL;
int dx[] = {-1, 0, 1 , 0};
int dy[] = {0, -1, 0, 1};
unordered_map<LL,LL> myHash;

LL bcnt = -1;
int bfs(int start) {
    queue<int> q;
    q.push(start);
    bcnt++;
    while(q.size()) {
        int t= q.front();
        myHash[t] = bcnt;
        int x = t / m, y = t % m;
        q.pop();
        
        for (int i = 0; i < 4; i ++) {
            int a = x + dx[i], b = y + dy[i];
            if (a >= n || a < 0 || b >= m || b < 0) {
                continue;
            }
            if (!st[a][b] && g[a][b] == '#') {
                q.push(a * m + b);
                st[a][b] = true;
            }  
        }
    }
    return 1;
}


 

long long qmi(long long a, long long k, long long p) {
    long long res = 1;

    while(k) {
        if (k & 1) res = (LL) res * a % p;
        k >>= 1;
        a = (LL)a * a % p;

    }
    return res;

}

int main() {

 
    cin >> n >> m;

    queue<int> q;
    long long red = 0;
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < m; j ++) {
            cin >> g[i][j];
            if (g[i][j] == '.') red ++;
        }

    long long sum = 0;
    for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++) {
        if (g[i][j] =='#' && st[i][j] == false )  {
            st[i][j] = true;
            sum += bfs(i * m + j);
        }
    }


    int res = 0;
    for (int x = 0; x < n; x ++)
    for (int y = 0; y < m; y ++) {
        if (g[x][y] == '.') {
            set<int> s;
            int cnt = 0;
            for (int i = 0; i < 4; i ++) {
                int a = x + dx[i], b = y + dy[i];
                if (a >= n || a < 0 || b >= m || b < 0) {
                    continue;
                }
                if (g[a][b] == '#') {
                    if (s.count(myHash[a * m + b]) > 0) {
                    } else {
                        cnt ++;
                        s.insert(myHash[a * m + b]);
                    }
                }
            }
            // cout << x << " " << y << endl;
            // cout << sum - (cnt - 1) << endl;
            res += sum - (cnt - 1);
        }
    }
 

    long long modInvQ = qmi(red, MOD - 2, MOD);

    // Calculate R = (P * modInvQ) % MOD
    long long R = (res * modInvQ) % MOD;
    cout << res << endl; 
    cout << R << endl;

}