#include<iostream>
#include<cstring>
#include<queue>
#include<unordered_map>
#include<set>
using namespace std;

const int N = 1010;
char g[N][N];
int st[N][N];
int n, m;
const int MOD = 998244353;

typedef long long LL;
int dx[] = {-1, 0, 1 , 0};
int dy[] = {0, -1, 0, 1};
unordered_map<int,int> myHash;

LL green = 0;
int bfs(int start) {
    queue<int> q;
    q.push(start);
    while(q.size()) {
        int t= q.front();
        myHash[t] = green;
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
    long long red = 0;
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < m; j ++) {
            cin >> g[i][j];
        }

    for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++) {
        if (g[i][j] =='#' && st[i][j] == 0 )  {
            st[i][j] = true;
            green ++;
            bfs(i * m + j);
        }
    }


    LL res = 0;
    for (int x = 0; x < n; x ++)
    for (int y = 0; y < m; y ++) {
        if (g[x][y] == '.') {
            red ++ ;
            set<int> s;
            for (int i = 0; i < 4; i ++) {
                int a = x + dx[i], b = y + dy[i];
                if (a >= n || a < 0 || b >= m || b < 0) {
                    continue;
                }
                if (myHash.count(a * m + b))
                s.insert(myHash[a * m + b]);
            }
            // cout << x << " " << y << endl;
            // cout << green - (cnt - 1) << endl;
            res += green - (s.size() - 1);
        }
    }
 

    // long long modInvQ = qmi(red, MOD - 2, MOD);

    // Calculate R = (P * modInvQ) % MOD
    LL R = (res % MOD * qmi(red, MOD - 2, MOD) % MOD);
    // cout << res << endl; 
    std::cout << R << endl;
    return 0;

}