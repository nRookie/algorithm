#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;



const int N = 2* 1e6 + 10, M = 4 * N;

typedef pair<int,int> PII;
int h[N], ne[M], e[M], w[M], idx;

void add (int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}


typedef long long ll;
ll exgcd(ll a, ll b, ll & x, ll&  y) {
    
        if (b == 0) {
            x = 1;
            return a;
        }
        ll d = exgcd(b, a % b, y , x);
        y -= a/b * x;  
        
        return d;
}



// a, 
// 
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<ll> a(n), b (m);
    	for(int i = 0 ; i < n ; i ++) scanf("%lld", &a[i]);
	for(int i = 0 ; i < m ; i ++) scanf("%lld", &b[i]);
    int x = 0, y = 0;
	for(int i = 1 ; i < n ; i ++) if(a[i] < a[x]) x = i;
	for(int i = 1 ; i < m ; i ++) if(b[i] > b[y]) y = i;
	if(b[y] > a[x]) swap(a[x], b[y]);
	if( (k & 1) == 0){
		x = 0, y = 0;
		for(int i = 1 ; i < n ; i ++) if(a[i] > a[x]) x = i;
		for(int i = 1 ; i < m ; i ++) if(b[i] < b[y]) y = i;
		swap(a[x], b[y]);
	}
	long long ans = 0;
	for(int i = 0 ; i < n ; i ++) ans += a[i];
	printf("%lld\n", ans);

 
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}