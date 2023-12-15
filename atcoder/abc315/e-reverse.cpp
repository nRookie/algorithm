#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;



const int N = 8*1e5 + 10;

int h[N], e[N], ne[N], idx;
int dh[N];
int d[N];

bool st[N];
void add (int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}
void dadd (int a, int b) {
    e[idx] = b, ne[idx] = dh[a], dh[a] = idx ++;
}
int main() {
    int n;
    cin >> n;

    memset(h, -1, sizeof h);
    memset(dh, -1, sizeof dh);
    vector<int> ans;
    for (int i = 1; i <= n; i ++) {
        int c;
        cin >> c;
        while(c --) {
            int x ;
            cin >> x;
            dadd (i, x); 
            d[x] ++;
        }
    }
    queue<int> q;
    q.push(1);

    for (int i = 1; i < n; i ++) {
        cout << d[i] << " ";
    }
    cout << endl;
    while(q.size()) {
        int t = q.front();
        q.pop();
        printf("%d deque\n", t);
        if (t != 1) ans.push_back(t);
        for (int i = dh[t]; ~i ; i = ne[i]) {
            int j = e[i];
            d[j] --;
            if (d[j] == 0) {
                q.push(j);
            }
        }
    }

    for (int i = ans.size() -1; i >= 0; i --) {
        cout << ans[i] << " ";
    }
    return 0;
}

/*

5
1 2
2 3 5
0 
1 2
0 
*/