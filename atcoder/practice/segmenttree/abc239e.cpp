#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 100010,M = 2 * N,K = 50;
int n,q;
int a[N];
int h[N],e[M],ne[M],idx;
int ans[N][K];
void add (int a,int b) {
	e[idx] = b;
	ne[idx] = h[a];
	h[a] = idx++;
}
void merge (int a,int b) {
	for (int i = 21;i <= 40;i++) ans[a][i] = ans[b][i - 20];
	sort (ans[a] + 1,ans[a] + 1 + 40,greater <int> ());
}
void dfs (int u,int fa) {
	ans[u][1] = a[u];
	for (int i = h[u];~i;i = ne[i]) {
		int j = e[i];
		if (j == fa) continue;
		dfs (j,u);
		merge (u,j);
	}
}
int main () {
	cin >> n >> q;
	for (int i = 1;i <= n;i++) cin >> a[i];
	memset (h,-1,sizeof (h));
	for (int i = 1;i <= n - 1;i++) {
		int a,b;
		cin >> a >> b;
		add (a,b),add (b,a);
	}
	dfs (1,-1);
	while (q--) {
		int v,k;
		cin >> v >> k;
		cout << ans[v][k] << endl;
	}
	return 0;
}