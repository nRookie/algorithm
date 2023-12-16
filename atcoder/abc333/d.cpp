#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;


const int N = 3 * 1e5 + 10, M = N * 2;

int h[N], e[M], ne[M], idx;
bool st[N];
void add (int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int n;

vector<int> ans;
int dfs(int u) {
    st[u] = true;
    int res = 1;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (st[j]) continue;
        res += dfs(j);
    }
    return res;
}
int main() {
    memset(h , -1 , sizeof h);
    cin >> n;
    for (int i = 0; i < n - 1; i ++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        add(b, a);
    }
    st[1] = true;
    for (int i = h[1]; ~i; i = ne[i]) {
        int j = e[i];
        
        ans.push_back(dfs(j));
    }
    
    sort(ans.begin(), ans.end());

    int res = 0;

    // for (int i = 0; i < ans.size(); i ++) {
    //      cout << ans[i] << " ";
    // }
    // cout << endl;
    for (int i = 0; i < ans.size() - 1; i ++) {
        res += ans[i];
    }
    cout << res + 1 << endl;

    return 0;
}