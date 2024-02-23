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



// s, of length n
// x is good if there exist a  l of length n.
// containing x ones, such that if each symbol si is replaced by si ^ li, then the string s becomes palindrome.
//

// t of length n + 1, where ti (0 <= i <= n) is euqal to 1 if number i is good, and 0 otherwise.


void solve() {
    int n;
    cin >> n;
    string s;

    cin >> s;

    string t(n + 1, '0');

    int ans = 0; // minimum number of differences to make `s` a palindrome

    int max_1 = 0; // tracking the middle middle element in case of odd length strings.
    int max_2 = 0; // max_2 for counting matching pairs

    // 0 1 2
    //
    // 
    for (int i = 0; i <= n / 2 - 1; ++ i) {
        if (s[i] == s[n - i - 1]) {
            max_2 ++;   
        } else {
            ans ++;  
        } 
    }
    if(n%2 == 1)
        max_1++;

    for (int j = 0; j <= max_2; j ++) {
        for (int k = 0; k <= max_1; k ++) {
            t[ans + j * 2 + k] = '1';
        }
    }

    cout << t << "\n";

 
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}