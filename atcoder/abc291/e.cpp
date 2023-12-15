#include<iostream>
#include<cstring>
#include<queue>
using namespace std;



const int N = 2e5 + 10;

int e[N], h[N], ne[N], idx;
int ind[N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}
int n, m;
int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while(m --) {
        int a, b;

        cin >> a>> b;
        add(a, b); 
        ind[b] ++;
    }

    queue<int> q;
    for (int i = 1; i <= n; i ++) {
        if (ind[i] == 0) {
            q.push(i);
        }
    }
    if(q.size() != 1) {
        cout << "No" << endl;
        return 0;
    }
    vector<int> res;

    while(q.size()) {
        int t = q.front();
        q.pop();
        res.push_back(t);
        int cnt = 0;
        for (int i = h[t]; ~i; i = ne[i] ) {
            int j = e[i];
            
            ind[j] --;

            if (ind[j] == 0) {
                q.push(j);
                cnt ++;
            }
        }
        if (cnt > 1) {
            cout << "No" << endl;
            return 0;
        } 
    }

    if (res.size() != n) {
        cout << "No" << endl;
        return 0;
    } else {
        cout << "Yes" << endl;
    }
    // 1
    // a3 a2 a4 a1
    //
    vector<int> a(res.size() + 1);
    for (int i = 0; i < res.size(); i ++) {
        //cout << res[i] << " ";
        a[res[i]] = i + 1;
    }
    // cout << endl;

    for (int i = 1; i < a.size(); i ++) {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;

}