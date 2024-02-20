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
    // 1 5 5 2

    // 1 

    // 14 3000000000 1000000000 500000000
    //                500000000
    // 7 * l + 2 * t
    // 2 * t + 2
    // 2

    ll task = (n - 1)/ 7 + 1;
    ll daywith2task = task / 2;
    ll daywith1task = task % 2;
    ll daywithNotask = n - daywith2task - daywith1task;

    ll pointWith2task = l + 2 * t;
    ll pointWith1task = l + t;

    ll pointWithNoTask = l;

    // cout << daywith2task << " " << daywith1task << " " << daywithNotask << endl;
    if (daywith2task) {
        if (P >= daywith2task * pointWith2task) {
            P -= daywith2task * pointWith2task;
            n -= daywith2task;
        } else {
            ll  day  = (P  + pointWith2task - 1)/ pointWith2task;
            cout << (n - day) << endl;
            return ;
        }
    }
    if (daywith1task) {
        if (P >= daywith1task * pointWith1task) {
            P -= daywith1task * pointWith1task;
            n -= daywith1task;
        } else {
            ll  day  = (P + pointWith1task - 1) / pointWith1task;
            cout << (n - day) << endl;
            return ;
        }
    }
    // cout << n << " " << P <<  endl;
    if (daywithNotask) {
        if (P >= daywithNotask * pointWithNoTask) {
            P -= daywithNotask * pointWithNoTask;
            n -= daywithNotask;
        } else {
            ll  day  = (P + pointWithNoTask - 1)/ pointWithNoTask;
            cout << (n - day) << endl;
            return ;
        }
    }
    cout << 0 << endl;
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}