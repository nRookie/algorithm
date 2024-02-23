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
// two operations

// pick i,  swap(i, i + 2)
// pick i,  reverse the order of letters formed by the range (i, i + k - 1) of the string.
//  you can make as amany step as you want.
// your task is to find the lexicographically smallest string you can obtain after some number of steps
// 
void solve() {
    int n, k;
    cin >> n >> k;
    
    string s;

    cin >> s;

    // 1 2 3 4 5
    // i = 1, k = 3
    // 5 4 3 2 1
    // 1 2 3 4
    // 1 0 1 0
    // 0 1 0 1
    // 1 0 1 0
    // 

    if (k & 1) {
        string odd, even;

        for (int i = 0; i < n; i ++) {
            if (i & 1) {
                odd += s[i];
            } else {
                even += s[i];
            }
        }

        sort(odd.begin(), odd.end());
        sort(even.begin(), even.end());
        string res = "";
        for (int i = 0; i < even.size(); i ++) {
            res += even[i];
            if (i < odd.size())
            res += odd[i];
        }

        cout << res << endl;
    } else {
        sort(s.begin(), s.end());
        cout << s << endl;
    }
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}