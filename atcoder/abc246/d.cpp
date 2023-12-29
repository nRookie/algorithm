#include<iostream>

using namespace std;
typedef long long  ll;

ll f(ll  a, ll b) {
    return a * a * a + a * a * b + b * b * a + b * b * b;
}


int main() {
    ll n;

    cin >> n;
    ll res = 1e18;
    for (ll a = 0; a <= 1e6; a ++) {
            ll l = 0, r = 1e6;
            while (l < r) {
                ll mid = l + r >> 1;
                if (f(a, mid) < n) {
                    l = mid + 1;
                } else {
                    r = mid;
                }

                // cout << l << " " << r << " " << res << endl;
                // if (res == 1) return 0;
            }
            res = min(res, f(a, l));
    }
    cout << res << endl;

    return 0;
}