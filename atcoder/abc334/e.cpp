#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

const int N = 1010;
char g[N][N];
bool st[N][N];
int n, m;
const int MOD = 998244353;

typedef long long LL;
int dx[] = {-1, 0, 1 , 0};
int dy[] = {0, -1, 0, 1};

int bfs(int start) {
    queue<int> q;
    q.push(start);
    while(q.size()) {
        int t= q.front();
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



int qmi(int a, int k, int p) {
    int res = 1;

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
    int red = 0;
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < m; j ++) {
            cin >> g[i][j];
            if (g[i][j] =='.')  {
                q.push(i * m + j);
                red ++;
            }
        }

    int sum = 0;
    while(q.size()) {
        int cnt = 1;
        memset(st, 0, sizeof st);
        int t = q.front();
        q.pop();
        int x = t / m, y = t % m;
        st[x][y] = true;
        bfs(t);

        for (int i = 0; i < n; i ++)
        for (int j = 0; j < m; j ++) {
            if (g[i][j] =='#' && st[i][j] == false )  {
                st[i][j] = true;
                cnt += bfs(i * m + j);
            }
        }

        sum += cnt;
    }
 
    long long modInvQ = qmi(red, MOD - 2, MOD);

    // Calculate R = (P * modInvQ) % MOD
    long long R = (sum * modInvQ) % MOD;

    cout << R << endl;

    // cout << (sum * 1.0)/(red * 1.0) << endl;

}