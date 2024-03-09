#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 2 * 1e6 + 10, M = 4 * N;

typedef pair<int, int> PII;
int h[N], ne[M], e[M], w[M], idx;

void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

typedef long long ll;
ll exgcd(ll a, ll b, ll &x, ll &y)
{

    if (b == 0)
    {
        x = 1;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;

    return d;
}

// you are playing a word puzzle. The puzzle starts with a 3 by 3 grid, where each cell contains
// either the letter A, B, or C

// The goal of this puzzle is to find the lexicographically smallest possible word of length 3.

//

void solve()
{
    int n = 3;
    vector<string> g(3);

    string res = "";
    for (int i = 0; i < n; i++)
        cin >> g[i];

    res = g[0];
    vector<vector<bool>> st(3, vector<bool>(3, false));
    int dx[] = {-1, -1, -1, 1 , 1, 1, 0, 0};
    int dy[] = {-1, 0, 1,  -1, 0, 1,  -1, 1 };

    function<void(int, int, int, string)> dfs = [&](int u, int x, int y, string path)
    {
        if (st[x][y])
            return;
        if (u == 3)
        {
            //cout <<"path is " <<  path << endl;
            if (res > path)
            {
                //cout << res <<  " res is bigger than path " << path <<  endl;
                res = path;
            }
            return;
        }
        st[x][y] = true;
        for (int i = 0; i < 8; i++)
        {
            int a = x + dx[i], b = y + dy[i];

            if (a < 0 || b < 0 || a >= 3 || b >= 3)
                continue;
            path += g[a][b];
            dfs(u + 1, a, b, path);
            path.pop_back();
        }
        st[x][y] = false;
    };

    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 3; j ++) {
            string path;
            path += g[i][j];
            dfs(1, i, j, path);
            path.pop_back();
            //cout << res << endl;
        }
    }

    cout << res << endl;
}

int main()
{
    solve();
}