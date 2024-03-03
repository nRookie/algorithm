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

// a,
// k gold coins

// gold coin worth g silver coins

// k * g silver coins among n people.

// nearest integer number of gold coin

// the rounding procedure is as follows, if an astrophysicist has bonus equal to x silver coins
// and we denote r = x mod g, then :

// if r >= [g / 2] , x + (g - r)

// x - r

// k * g
void solve()
{

    long long n, k, g;
    scanf("%lld %lld %lld", &n, &k, &g);

    long long stolen = min((g - 1) / 2 * n, k * g);
    long long rest = (k * g - stolen) % g;

    if (rest > 0)
    {
        stolen -= (g - 1) / 2;
        long long last = ((g - 1) / 2 + rest) % g;

        if (last * 2 < g)
        {
            stolen += last;
        }
        else
        {
            stolen -= g - last;
        }
    }
    // g - last = g - ( (g - 1) / 2) - rest;
    // 

    printf("%lld\n", stolen);
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }
}


// stolen= 150
// rest= 30
// g = 100
// 101
// 79
// stolen = 101 - 21 = 80
