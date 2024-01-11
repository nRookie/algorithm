#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
using LL = long long;

const int mo = 998244353;

long long qpower(long long a, long long b)
{
    long long qwq = 1;
    while (b)
    {
        if (b & 1)
            qwq = qwq * a % mo;
        a = a * a % mo;
        b >>= 1;
    }
    return qwq;
}

long long inv(long long x) { return qpower(x, mo - 2); }

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int h, w;
    cin >> h >> w;
    vector<string> s(h);
    int greeen = 0;
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
        {
            cin >> s[i][j];
            if (s[i][j] == '#')
            {
                greeen++;
            }
        }

            vector<int> dfn(h * w), low(h * w);
            int time = 0;
            int block = 0;
            auto tr = [&](int x, int y)
            { return x * w + y; };
            auto invtr = [&](int x) -> array<int, 2>
            { return {x / w, x % w}; };
            array<int, 4> dx{-1, 0, 1 , 0};
            array<int, 4> dy{0, -1, 0, 1};
            vector<vector<int>> son(h * w);
            vector<int> f(h * w);
            auto dfs = [&](auto self, int u, int fa) -> void
            {
                ++time;
                f[u] = fa;
                dfn[u] = low[u] = time;
                auto [x, y] = invtr(u);
                for (int i = 0; i < 4; ++i)
                {
                    int nx = x + dx[i], ny = y + dy[i];
                    if (nx < 0 || ny < 0 || nx >= h || ny >= w || s[nx][ny] == '.')
                        continue;
                    int nu = tr(nx, ny);
                    if (nu == fa)
                        continue;
                    if (dfn[nu])
                        low[u] = min(low[u], dfn[nu]);
                    else
                    {
                        son[u].push_back(nu);
                        self(self, nu, u);
                        low[u] = min(low[u], low[nu]);
                    }
                }
            };
            for (int i = 0; i < h; ++i)
                for (int j = 0; j < w; ++j)
                {
                    auto it = tr(i, j);
                    if (s[i][j] == '#' && !dfn[it])
                    {
                        ++block;
                        dfs(dfs, it, it);
                    }
                }
            LL ans = 0;
            for (int i = 0; i < h; ++i)
                for (int j = 0; j < w; ++j)
                {
                    if (s[i][j] == '#')
                    {
                        int cnt = 0, u = tr(i, j);
                        printf("i:%d j: %d dfn: %d low: %d \n", i, j, dfn[u], low[u]);
                        for (auto &v : son[u])
                        {
                            cnt += (dfn[u] <= low[v]);
                        }
                        ans += block - 1 + cnt + (f[u] != u);
                    }
                }

            cout << ans << endl;
            ans = ans % mo * inv(greeen) % mo;

            cout << block << " " << greeen << endl;
            cout << ans << '\n';

            return 0;
        }
