#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<queue>
#include<limits>
#include <optional>
using namespace std;



const int N = 1e6 + 10, M = 3 * N;
typedef long long ll;
typedef pair<int,int> PII;

struct train {
    unsigned long first_train;
    unsigned long interval;
    unsigned long count;
    unsigned long distance;

    optional<unsigned long> get_last_train(unsigned long time_limit) const {
        if (time_limit < first_train + distance)
            return nullopt;
        return first_train + min(count - 1, (time_limit - first_train -  distance) / interval) * interval;
    }
};

int h[N], ne[M], e[M], idx;
train w[M];
ll first[M], interval[M], last[M];

void add (int a, int b, int c, int l, int d, int k) {
    e[idx] = b, ne[idx] = h[a], w[idx].distance = c, w[idx].first_train = l, w[idx].interval = d, w[idx].count = k, h[a] = idx ++;
}


int n, m;
 

int main() {
    int n, m;
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m --) {
        int l,d,k,c, a, b;

        cin >> l >> d >> k >> c >> a >> b;

        add(b, a, c, l, d, k);
    }

    priority_queue<pair<unsigned long, unsigned>> pq;

    vector<unsigned long> ans(n + 1);
    pq.emplace(ans.back() = numeric_limits<unsigned long>::max(), n);

    // A -> B,
    // t -> t + c

    // B -> A
    // -t - c -> -t
    // -t 
    while(!empty(pq)) {
        const auto[time_limit, u] {pq.top()};
        pq.pop();

        if (ans[u] > time_limit) continue;


        for (int i = h[u]; ~i; i = ne[i]) {
            int j = e[i];
            const auto next = j;
            const auto next_time = w[i].get_last_train(time_limit);
            cout << *next_time << endl;
            if (next_time && ans[next] < *next_time) {
                pq.emplace(ans[next] = *next_time, next);
            }
        }
    }

        // Output the answer for each station except for the last one
    for (int i = 1; i < n; i ++)
        if (ans[i])
            cout << ans[i] << endl;
        else
            cout << "Unreachable" << endl;
    
    return 0;
    
}