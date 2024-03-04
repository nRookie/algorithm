#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>
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
    auto dist = [](int x1, int y1, int x2, int y2) {
        return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    };
    int px, py, ax, ay, bx, by;
    cin >> px >> py >> ax >> ay >> bx >> by;
    double pa = dist(px, py, ax, ay), pb = dist(px, py, bx, by);
    double oa = dist(0, 0, ax, ay), ob = dist(0, 0, bx, by);
    double ab = dist(ax, ay, bx, by);
    double ans = 1e9;
    ans = min(ans, max(pa, oa));
    ans = min(ans, max(pb, ob));
    ans = min(ans, max({ab / 2, pa, ob}));
    ans = min(ans, max({ab / 2, pb, oa}));
    cout << setprecision(10) << fixed << ans << '\n';
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}