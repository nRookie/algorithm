#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;



vector<string> ans;
vector<bool> st;

int n;
string s;
int k;
void dfs(int u, string path) {
    if (u == n) {
        ans.push_back(path);
        return ;
    }

    if (ans.size() > k) return ;

    for (int i = 0; i < n; i ++) {
        if (!st[i] ) {
            if (i > 0 && s[i] == s[i - 1] && st[i - 1]) continue;
            st[i] = true;
            path += s[i];
            dfs(u + 1, path);
            path.pop_back();
            st[i] = false;
        }
    }
}
int main() {
 
    cin >> s;
    cin >> k;
 
    n = s.size();
    st.resize(n, 0);
    sort(s.begin(), s.end());

     dfs(0, "");

    // for (auto a : ans) {
    //     cout << a << endl;
    // }
    cout << ans[k - 1] << endl;
}