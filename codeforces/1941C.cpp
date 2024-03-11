#include <iostream>
#include <string>
using namespace std;


void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if ((i + 2 < n && s[i] == 'm' && s[i+1] == 'a' && s[i+2] == 'p') || (i + 2 < n && s[i] == 'p' && s[i+1] == 'i' && s[i+2] == 'e')) {
            cnt++;  
            i += 2;
        }
    }
    cout << cnt << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
