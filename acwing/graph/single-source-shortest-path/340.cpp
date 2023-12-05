#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int N = 1010, M = 20010, INF = 0x3f3f3f3f;
int n, p, k;
int h[N], e[M], ne[M], w[M], idx;
bool st[N];
int dist[N];

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

bool check(int mid) {
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    dist[1] = 0;
    queue<int> q;
    q.push(1);

    while (!q.empty()) {
        int t = q.front();
        q.pop();
        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            int c = dist[t] + (w[i] > mid);
            if (dist[j] > c) {
                dist[j] = c;
                if (!st[j]) {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }

    return dist[n] <= k;
}

int main() {
    cin >> n >> p >> k;
    memset(h, -1, sizeof h);
    for (int i = 0; i < p; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }

    int l = 0, r = 1000001;  // 修改上界为 1000001
    while (l < r) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }

    if (l == 1000001) cout << -1 << endl;  // 修改检查条件
    else cout << l << endl;

    return 0;
}
