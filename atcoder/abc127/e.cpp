#include<iostream>
using namespace std;

const int N = 200005, mod = 1000000007;
typedef long long ll;

ll fact[N], infact[N];
ll ans;

ll qmi(int a, int k, int p) {
    ll ans = 1;
    while(k) {
        if (k & 1) ans = (ll)ans * a % p;
        k >>= 1;
        a = (ll)a * a % p;
    }
    return ans;
}

void init() {
    fact[0] = infact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = fact[i - 1] * i % mod;
        infact[i] = infact[i - 1] * qmi(i, mod - 2, mod) % mod;
    }
}

ll C(int a, int b) {
    if (b > a) return 0; // Just in case
    return fact[a] * infact[a - b] % mod * infact[b] % mod;
}

int main() {
    init();

    int n, m, k;
    cin >> n >> m >> k;
    ans = 0; // Initialize ans to 0
    for (int i = 1; i < n; i++) ans = (ans + (ll)i * (n - i) % mod * m % mod * m) % mod;
    for (int i = 1; i < m; i++) ans = (ans + (ll)i * (m - i) % mod * n % mod * n) % mod;
    ans = ans * C(n * m - 2, k - 2) % mod;
    cout << ans << endl;
}
