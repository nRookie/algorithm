#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1e6 + 10, M = 4 * N;

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

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    ll ans = 0;
    for (int i = 0; i < 26; i++)
    {
        int index = s.find_first_of('a' + i);
        if (index != -1)
        {
            ans += n - index;
        }
    }

    cout << ans << '\n';
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
// 0 1 2 3 4 5 6
//
// 1 23 4 5 6

// 1 2 3 4 5 6 7 8 9 10
// 4 ge 1 ,  2 ge 2
// i = 4, j = 2
// 5 6 7 8 9 10
// 5 7 8 9 10
// 5 8 9 10
// 5 9 10
// 5,8,9,10
// two sequences of operations such that the first operation always comes before the second result in the same string.
// first operation always comes before the second result in the same string.
// consider for the (i1, j1) pair, the resulting string is the same as for the (i2, j2) pair.
// we can see that i1 + j1 = i2 + j2,
// because the number of erased letters should be the same to get strings of the same length.
// i1 = 1 j1 = 2
// i2 = 2 j1 = 1
// 123456
// 23456
// 2456

// i = 5, j = 2

// 123456789
// 6789
// 69

// i = 4, j = 3
// 123456789
// 56789
// 59

// Si + 1 = Sj + 1
// Next, 𝑠𝑖1+1=𝑠𝑖2+1, as those are the first letters of two resulting equal strings.
//

//  if after applying first operation op1 times , the first letter is not its first occurrence,
// then any subsequent result could have been achieved by less operations of the first type by removing first character
// and then by removing the second character until we reach op1 operations in total.

// this means we need to consider using the second operation only at the first occurrence of the letter.

// 1314
// 314
// 14
// 4
//

// the final solution can look like this , : for each letter a...z find it's first occurrence.
// if the letter is found, any number of second operation leads to a different result.
// thus we can just calculate

// abcd
// abcd acd ad a
// bcd bc b
// cd c
// d

// aaabcd
// aaabcd aabcd abcd acd ad a
// bcd bd b
// cd c
// d