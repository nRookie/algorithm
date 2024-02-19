#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;



const int N = 1e6 + 10, M = 4 * N;

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
    int n, k, x;
    cin >> n >> k >> x;

    vector<int> a(n);
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
    }

    // 
    sort(a.begin(), a.end());

    vector<int> pre(n + 1, 0);

    for (int i = 1 ; i <= n; i ++) {
        pre[i] = pre[i - 1] + a[i - 1];
    }

    // n = 5, x  k = 2,  x = 2
    int ans = INT_MIN;

    for (int i = 0; i <= k ; i ++) {
        int i1 = n - i;
        ans = max(ans, pre[max(0, i1 - x)] - (pre[i1] - pre[max(0, i1 - x) ] ));
    }
    cout << ans << endl;
}
// 1. alice remove at most k elements from the array
// 2. bob will multiply at most x elements of the array by -1.


// Alice wants to maximize the sum of elements of the array while Bob wants to minimize it.
// Find the sum of elements of the array after the game if both players play optimally.

        // 0 1 2 3 4 5
        // 1 2 3 4 5
        // 0 1 3 6 10 15
        //  
        //   i ..j
        // 
        // pre[j] - pre[i - 1]
        // 

        // n = 5, x =2
        // i1 = 5 i1 - x = 3
        // pre[3] =6 
        // pre[5] - pre[3] = 9
        // printf("i1 = %d, k = %d, diff is : %d pre: %d, pre %d \n", i1, i, pre[max(0, i1 - x)] - (pre[i1] - pre[max(0, i1 - x) ]) , 
        // pre[ max(0, i1 - x)] , pre[i1] - pre[max(0, i1 - x) ] );

int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}