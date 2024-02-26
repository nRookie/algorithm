#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;


typedef long long ll;
const int N = 2 * 1e6 + 10, M = 3 * N; 


int h[N], idx, ne[M], e[M];

struct train {
    ll count;
    ll interval;
    ll distance;
    ll first_train;
};

train w[M];


ll INF = 2e18 + 10;


ll getLastTrain(train & t, ll time_limit) {
    if (time_limit < t.first_train + t.distance) {
        return -1;
    }
    return t.first_train +  min(t.count - 1, ( time_limit - t.first_train - t.distance) / t.interval) * t.interval;
}
void add(int a, int b, int c, int l, int d, int k) {
    e[idx] = b, ne[idx] = h[a], w[idx].distance = c, w[idx].first_train = l, w[idx].count = k, w[idx].interval = d, h[a] = idx ++;
}

int main() {

    int n, m;
    memset(h, -1, sizeof h);
    cin >> n >> m;

    while(m --) {
        int l, d, k, c, a, b;
        cin >> l >> d >> k >> c >> a >> b;
        add (b, a, c,l, d, k);
    }
    vector<ll> ans(n + 1, 0);
    priority_queue<pair<ll, int>> heap;

    ans[n] = INF;
    heap.push({ans[n], n});
    while(heap.size()) {
        auto [time_limit, u] = heap.top();
        heap.pop();

        if (ans[u] > time_limit) continue;
        for (int i = h[u]; ~i; i = ne[i]) {
            int next = e[i];
            ll lastTrain = getLastTrain(w[i], time_limit);
            // cout << lastTrain << endl;
            if (lastTrain != -1 && ans[next] < lastTrain  ) {
                ans[next] = lastTrain;
                heap.push({ans[next], next});
            }

        }
    }

    for (int i = 1; i < n; i ++) {
        if (ans[i]) {
            cout << ans[i] << endl;
        } else {
            cout << "Unreachable" << endl;
        }
    }

    return 0;


}