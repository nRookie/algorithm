#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


typedef long long ll;
void solve()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    ll minDiff = 100;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++)
    {
        ll remainder = a[i] % k;

        if (remainder == 0)
        {
            cout << 0 << endl;
            return;
        }
        else
        {
            minDiff = min(minDiff, k - remainder);
        }
    }

    if (k == 4)
    {
        k = 2;
        ll cnt0 = 0;
        ll cnt1 = 0;
        ll diff = 100;
        for (int i = 0; i < n; i++)
        {
            ll remainder = a[i] % k;

            if (remainder == 0)
            {
                cnt0++;
            }
            else
            {
                cnt1++;
            }
        }

        // cout << minDiff << " " << diff << endl;
        if (cnt0 >= 2) {
             cout << 0 << endl;
        } else if (cnt1 + cnt0 >= 2) {
            if (cnt0) {
                cout << min(1ll, minDiff) << endl;
            } else {
                cout << min(2ll, minDiff) << endl;
            }
        }
        else {
            cout << minDiff << endl;
        }
    } else
    cout << minDiff << endl;
    // a mod k = r
    // a = k * q + r

    // (a + x) mod k = 0
    // a + x = k * (q + 1)
    /// kq + r + x = k(q + 1)
    // x  = k - r
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