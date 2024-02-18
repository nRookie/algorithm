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
       
        vector<bool> found(k, false);
        int count = 0;
        string res = "";
        for (auto c : s) {
            if (res.size() == n) 
                break;
            count +=(!found[c - 'a']);
            found[c - 'a'] = true;
            // cout << count << " " << c << " res: " << res << " " << endl;
            if (count == k) {
                fill(found.begin(), found.end(), 0);
                count = 0;
                res += c;
            }
        }

        if (res.size() == n)
            cout <<"YES\n";
        else {
            cout <<"NO\n";
            for (int i = 0; i < k; i ++) {
                if (!found[i]) {
                    while(res.size() < n)
                        res +=(char)('a' + i);
                }
            }
            cout << res << "\n";
        }
    }
    return 0;
}