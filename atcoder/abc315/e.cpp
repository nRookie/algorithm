#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<set>
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

vector<int> block;
// 不能防止去读分支上的书，（不是1的依赖的分支。）

set<int> in1;

void dfs(int u) {
    st[u] = true;
    for (int i = dh[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!st[j]) {
            block.push_back(j);
            in1.insert(j);
            dfs(j);
        }
    }
}
void print() {
    for (int i = 1; i <= 10; i ++) {
        cout << d[i] << " ";
    }
    cout << endl;
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
        d[i] = c;
        while(c --) {
            int x ;
            cin >> x;
            add (x, i);
            dadd (i, x);
        }
    }

    if (d[1] == 0) {
        cout << 0 << endl;
        return 0;
    }


    dfs(1);
    queue<int> q;


    for (int i = 1; i <= n; i ++) {
        // printf("i : %d, %d\n", i, in1.count(i));
        if(d[i] == 0 && in1.count(i)) {
            q.push(i);
            // printf("enqueue : %d \n", i);
        }
    }

    while(q.size()) {
        int t = q.front();
        q.pop();
        if (t == 1) break;
        ans.push_back(t);
        // printf("t:deque  %d \n", t);
        for (int i = h[t]; ~i ; i = ne[i]) {
            int j = e[i];
            d[j] --;
            // printf("d[j] : %d, in1.count(%d) = %d \n", d[j], j,  in1.count(j));
            if (d[j] == 0 && in1.count(j)) {
                // printf("enqueue : %d \n", j);
                q.push(j);
            }
        }
    }

    for (auto x: ans) cout << x << " ";
    cout << endl;
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