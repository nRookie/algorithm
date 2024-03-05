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



// n by n, the value of n is even.
// she wants to change some characters so that her matrix becomes a perfect square. A matrix is called a perfect square if it remains unchanged when rotated 90 clockwise once.

// Here is an example of rotating a matrix by 90

// a b b a
// b c b b
// b c c b
// a b b a

//
void solve() {
    int ans = 0;
    int n;
    cin >> n;
    vector<string> a(n, "");

    for (int i = 0; i < n; i ++) cin >> a[i];
    for (int i = 0; i  * 2 < n; i ++)
        for (int j = 0; j * 2 < n; j ++) {
            vector<char> M {a[i][j], a[n - 1 - j][i], a[n - 1 - i][n - 1 - j],a[j][n - 1-i] };
            char c = *max_element(M.begin(), M.end());

            for (char m: M) {
                ans += c - m;
            }
        }
    
    cout << ans << endl;
    // a[i][j]   a[j][n - 1 - i];
    // a[n - 1 - j][i]    a[i][j];
    // a[n - 1 - i][n - 1 - j] takes the position of element a[n - 1 - j][i].
    //  

    // 0 1 2         n = 3,      j = 0, i = 0 
    //0    
    //1
    //2
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}