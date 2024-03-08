#include <iostream>
using namespace std;
const int N = 2010;
int n,m;
char a[N][N];
int l[N][N],r[N][N],u[N][N],d[N][N];
int main () {
	cin >> n >> m;
	for (int i = 1;i <= n;i++) cin >> a[i] + 1;
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= m;j++) {
			if (j - 1 >= 1 && a[i][j - 1] != '#') l[i][j] = l[i][j - 1];
			else l[i][j] = j;
		}
		for (int j = m;j >= 1;j--) {
			if (j + 1 <= m && a[i][j + 1] != '#') r[i][j] = r[i][j + 1];
			else r[i][j] = j;
		}
	}
	for (int j = 1;j <= m;j++) {
		for (int i = 1;i <= n;i++) {
			if (i - 1 >= 1 && a[i - 1][j] != '#') u[i][j] = u[i - 1][j];
			else u[i][j] = i;
		}
		for (int i = n;i >= 1;i--) {
			if (i + 1 <= n && a[i + 1][j] != '#') d[i][j] = d[i + 1][j];
			else d[i][j] = i;
		}
	}
	int ans = 0;
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= m;j++) {
			if (a[i][j] != '#') ans = max (ans,d[i][j] - u[i][j] + 1 + r[i][j] - l[i][j] + 1 - 1);
		}
	}
	cout << ans << endl;
    return 0;
}