#include<iostream>
#include<cstring>
#include<queue>
using namespace std;


const int N = 2 * 1e5 + 10, M = 2 * 1e5 + 10;

int h[N], ne[M], e[M], idx;

int ind[N];
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}


int n, m;
int main() {
    memset(h , -1, sizeof h);
    cin >> n, m;

    while(m --) {
        int a, b;
        cin >> a>> b;
        // a - > b
        add(a, b);
        ind[b]++;
    }
    queue<int> q;
    for (int i = 1; i <= n; i ++) {
        if (ind[i] == 1) {
            q.push(i);
        }
    }
    vector<int> ans;

    while(q.size()) {
        int t = q.front();
        q.pop();
        ans.push_back(t);
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            ind[j] --;

            if(ind[j] == 0) {
                q.push(j);
            }
        }
    }

    for (auto x: ans) cout << x << " ";

    cout << endl;

    return 0;

}