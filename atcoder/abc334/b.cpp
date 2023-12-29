#include<iostream>
#include<cmath>

using namespace std;
typedef long long ll;


ll myfloor(ll x, ll m) {
    return (x % m + m) % m;
}

// -2 % 3  = -2 = (-1  * 3 ) + 1
// 


int main() {
    ll a, m, l, r;

   cin >> a >> m >> l >> r;
    // a - l > 0  a is at the right side of the l
    // a - l < 0 a is at the left side of the l.

    // r - a > 0 r is at the right side of the a,
    // r - a < 0 r is at the left side of the a.
   ll leftMost = l + myfloor(a - l, m) ;
   ll rightMost = r - myfloor(r - a, m);
   ll res = (rightMost - leftMost) / m + 1;
   //cout << leftMost << " " << rightMost << endl;
   cout << res << '\n';
    return 0;
}