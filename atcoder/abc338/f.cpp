#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const long long INF = LLONG_MAX / 3;

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<long long>> dist(N, vector<long long>(N, INF));
    for (int i = 0; i < N; ++i) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < M; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        --u; --v;
        dist[u][v] = w;
    }

    for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    vector<vector<long long>> dp(1 << N, vector<long long>(N, INF));
    for (int i = 0; i < N; ++i) {
        dp[1 << i][i] = 0;
    }

    for (int mask = 1; mask < (1 << N); ++mask) {
        for (int i = 0; i < N; ++i) {
            if ((mask & (1 << i)) == 0) continue;
            for (int j = 0; j < N; ++j) {
                if (dist[j][i] < INF) {
                    dp[mask][i] = min(dp[mask | (1 << j)][j] , dp[mask][i] + dist[i][j]);
                }
            }
        }
    }

    long long answer = INF;
    for (int i = 0; i < N; ++i) {
        answer = min(answer, dp[(1 << N) - 1][i]);
    }

    if (answer == INF) {
        cout << "No" << endl;
    } else {
        cout << answer << endl;
    }

    return 0;
}
