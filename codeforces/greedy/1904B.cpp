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
    int n;
    cin >> n;
    vector<PII> a(n); // n positive integer
    // score is greater than or equal to ai, i can increase my score by add ai to my score remove ai from the array.

    // for each index i,
    // output the maximum number of additional array elements that you can remove if you remove ai and then set your score to ai.
    // Note that removal of ai should not be counted in the answer.
    for (int i = 0; i < n; i ++) {
        int x;
        cin >> x;
        a[i] = {x, i};
    }

    sort(a.begin(), a.end());
    vector<int> res(n, 0);
    vector<ll> pre(n + 1);
    for (int i = 1; i <= n; i ++) {
        pre[i] = pre[i - 1] + a[i - 1].first;
    }
    // 1 2 4 5 20
    // 1 3 7 12 20

    // 1 3 
    res[a[n - 1].second] = n - 1;
    for (int i = n - 2; i >= 0; i --) {
        // cout << "pre" << pre[i + 1] << " " << a[i + 1].first << endl;
        if (pre[i + 1] >= a[i + 1].first) {
            res[a[i].second] = res[a[i + 1].second];
        } else {
            res[a[i].second] = i;
        }
    }

    for (auto r: res) cout << r << " ";
    cout << '\n';

    //
 
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}