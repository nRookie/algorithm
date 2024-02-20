#include<iostream>
#include<vector>
#include<algorithm>
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



// n days, at least P  point
// practical tasks,  attending lessons.
//  t                   l
// tasks are unlocked each week
// day 1,  8 , 15

// attend a lesson,  can solve no more than 2 tasks.


// find the maximum day he can rest


void solve() {
    ll n, P, l, t;
    cin >> n >> P >> l >> t;

    ll task = (n - 1)/ 7 + 1;

    int left = 0ll , right = n;

    auto calc = [&](ll k) {
        return min(task, 2 * k) * t + k* l;
    };
    while (left < right) {
        ll mid = (left + right) >> 1;
        if (calc(mid) >= P) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    cout << n - left << '\n';
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}