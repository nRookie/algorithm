#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    int t;

    cin >> t;

    while (t --) {
        int n, k, m;
        cin >> n >> k >> m;
        string s;
        cin >> s;
        int cnt[26] = {0};
        for (auto &c : s) {
            cnt [c - 'a'] ++;
        }
        bool flag = true;
        int less = -1;
        for (int i = 0; i < k; i ++) {
            if (cnt[i] < n) {
                flag = false;
                less = i;
                break;
            }
        }
        // cout <<flag <<  endl;

        if (flag) {
            cout << "YES" << '\n';
        } else {
            cout << "NO" << "\n";
            for (int i = 0; i < n; i ++)
                cout << char('a' + less);
            cout << '\n';
        }
    }
    return 0;
}