#include <iostream>
#include <algorithm> 

using namespace std;


typedef long long  ll;
ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}


ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

int main() {
    ll N, M, K;
    cin >> N >> M >> K;

    ll low = 1, high = 2e18, mid, ans = -1;

    while (low <= high) {
        mid = (low + high) / 2;

        ll total = mid / N + mid / M - 2 * (mid / lcm(N, M));

        if (total < K) {
            low = mid + 1;
        } else {
            ans = mid;
            high = mid - 1;
        }
    }

    cout << ans << endl;

    return 0;
}
