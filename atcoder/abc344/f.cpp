#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <tuple>
#include <queue>
using namespace std;

const long long INF = 1e18;

int main() {
    int N;
    cin >> N;
    vector<vector<int>> P(N, vector<int>(N)), R(N, vector<int>(N)), D(N, vector<int>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> P[i][j];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N - 1; j++)
            cin >> R[i][j], R[i][j + 1] = R[i][j];
    for (int i = 0; i < N - 1; i++)
        for (int j = 0; j < N; j++)
            cin >> D[i][j], D[i + 1][j] = D[i][j];
    vector<vector<long long>> dp(N, vector<long long>(N, INF));
    dp[0][0] = 0;
    priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<>> pq;
    pq.push({0, 0, 0});
    while (!pq.empty()) {
        auto [cost, x, y] = pq.top();
        pq.pop();
        if (dp[x][y] < cost) continue;
        if (x == N - 1 && y == N - 1) break; // Reached destination
        // Try to stay
        int nextCost = P[x][y] + cost;
        if (nextCost < dp[x][y]) {
            dp[x][y] = nextCost;
            pq.push({dp[x][y], x, y});
        }
        // Try to move right
        if (y + 1 < N && cost >= R[x][y] && cost - R[x][y] + 1 < dp[x][y + 1]) {
            dp[x][y + 1] = cost - R[x][y] + 1;
            pq.push({dp[x][y + 1], x, y + 1});
        }
        // Try to move down
        if (x + 1 < N && cost >= D[x][y] && cost - D[x][y] + 1 < dp[x + 1][y]) {
            dp[x + 1][y] = cost - D[x][y] + 1;
            pq.push({dp[x + 1][y], x + 1, y});
        }
    }
    cout << dp[N - 1][N - 1] << endl;
    return 0;
}
