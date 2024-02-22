#include<algorithm>
#include<iostream>
#include<utility>
#include<queue>
#include<deque>
#include<cmath>
#include<set>
#include<map>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pa;
const ll N = 2e5 + 10, MOD = 998244353, INF = 0x7fffffff;
class cmp {
public:
	bool operator() (const pa& x, const pa& y)const {
		if (x.first != y.first)return x.first > y.first;
		else return x.second < y.second;
	}
};
ll t, n, x, k;
void solve() {
	vector<ll> pre;
	ll cnt = 0;
	ll cnt1 = 0;
	ll num = 0;
	string s;
	cin >> n >> s;
	for (int i = n - 1; i >= 0; i--) {
		if (s[i] == '0') pre.push_back(num), cnt++;
		else num++, cnt1++;
	}
	for (int i = 0; i < pre.size(); i++)if (i != 0)pre[i] += pre[i - 1];
	for (int i = 1; i <= n; i++) {
		if (i > cnt ) {
			cout << -1 << " ";
			continue;
		}
		cout << pre[i - 1] << " ";
	}
	cout << '\n';
	
}
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> t;
	while (t--) {
		solve();
	}
}