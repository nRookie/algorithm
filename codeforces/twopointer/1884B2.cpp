#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
using ll = long long;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    reverse(s.begin(), s.end());
    vector<int> f;  // f[i] = number of one before position i
    int one = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '0') {
            f.push_back(one);
        } else {
            one += 1;
        }
    }
    // 10101
    //
    //  f            one
    //                 1
    //   1             2
    //   1 2           
    //   1 2           3
    //  

    //     x sum 
    //     1   1
    //     2   3
    //    
    // 10101
    // 
    // 0001000011000    
    // f                  one
    // 000                 1
    // 000x1111xx          3
    // 0001111xx333        
    
    // 000010000001000001
    // 1110
    // xxx3
    // 11101111011110
    // xxx3xxxx7xxxx11
    // xxx3xxxx7xxxx11
    // 3
    // 00012347101316
    ll sum = 0, k = 0;
    for (int x : f) {
        cout << (sum += x) << " ";
    }
    for (int i = 0; i + size(f) < n; ++i) {
        cout << -1 << " ";
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test = 1;
    cin >> test;

    while (test--) {
        solve();
    }

    return 0;
}
