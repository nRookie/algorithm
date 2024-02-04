#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <array>

using namespace std;

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

int main() {
    int N;
    cin >> N;
    vector<string> grid(N);
    for (int i = 0; i < N; ++i) {
        cin >> grid[i];
    }

    vector<pair<int, int>> positions;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == 'P') {
                positions.push_back({i, j});
            }
        }
    }

    queue<tuple<int, int, int, int, int>> q;
    vector<vector<vector<vector<bool>>>> visited(N, vector<vector<vector<bool>>>(N, vector<vector<bool>>(N, vector<bool>(N))));
    q.push({positions[0].first, positions[0].second, positions[1].first, positions[1].second, 0});
    visited[positions[0].first][positions[0].second][positions[1].first][positions[1].second] = true;

    while (!q.empty()) {
        auto [x1, y1, x2, y2, move_count] = q.front(); q.pop();
        
        if (x1 == x2 && y1 == y2) {
            cout << move_count << endl;
            return 0;
        }

        for (int i = 0; i < 4; ++i) {
            int nx1 = x1 + dx[i], ny1 = y1 + dy[i], nx2 = x2 + dx[i], ny2 = y2 + dy[i];
            if (nx1 < 0 || nx1 >= N || ny1 < 0 || ny1 >= N || grid[nx1][ny1] == '#') {
                nx1 = x1; ny1 = y1;
            }
            if (nx2 < 0 || nx2 >= N || ny2 < 0 || ny2 >= N || grid[nx2][ny2] == '#') {
                nx2 = x2; ny2 = y2;
            }
            if (!visited[nx1][ny1][nx2][ny2]) {
                q.push({nx1, ny1, nx2, ny2, move_count + 1});
                visited[nx1][ny1][nx2][ny2] = true;
            }
        }
    }
    cout << -1 << endl;
}
