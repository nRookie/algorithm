#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);

    // Reading input arrays
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < m; ++i)
        cin >> b[i];

    // Sorting: a in ascending and b in descending order
    sort(a.begin(), a.end());
    sort(b.rbegin(), b.rend()); // Sorting b in descending order directly

    long long maxdiff = 0;

    long long diff = 0;

    vector<int> c(n);

    // a: 1 2 3    n
    // b: 1 2 3 4  m
    // b: 1 2 3 4 5 
    // 4 - 3 = 1 5 - 3 = 2
    for (int i = 0; i < n; i ++) {
        c[i] = b[m - n + i];
        diff += abs(c[i] - a[i]);
    }
    maxdiff = diff;
    for (int k = 0; k < n; k ++) {
        diff -= abs(c[k] - a[k]);
        c[k] = b[k];
        diff += abs(c[k] - a[k]);
        maxdiff = max(maxdiff, diff);
    }

    cout << maxdiff << endl;


    
}
int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}
