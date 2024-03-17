#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX = 11;
int H, W, N;
vector<pair<int, int>> tiles;
bool grid[MAX][MAX];
bool visited[MAX][MAX][1 << MAX]; // State caching (example, might need adjustment)

bool fits(int tileH, int tileW, int x, int y) {
    if (x + tileH > H || y + tileW > W) return false;
    for (int i = x; i < x + tileH; ++i)
        for (int j = y; j < y + tileW; ++j)
            if (grid[i][j]) return false;
    return true;
}

void placeTile(int tileH, int tileW, int x, int y, bool place) {
    for (int i = x; i < x + tileH; ++i)
        for (int j = y; j < y + tileW; ++j)
            grid[i][j] = place;
}

int getBitMask() {
    int mask = 0;
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j)
            mask |= (grid[i][j] << (i * W + j));
    return mask;
}

bool dfs(int idx) {
    if (idx == N) {
        for (int i = 0; i < H; ++i)
            for (int j = 0; j < W; ++j)
                if (!grid[i][j]) return false;
        return true;
    }
    int mask = getBitMask();
    if (visited[idx][H][mask]) return false;
    visited[idx][H][mask] = true;

    auto [tileH, tileW] = tiles[idx];
    for (int rot = 0; rot < 2; ++rot) {
        for (int x = 0; x < H; ++x) {
            for (int y = 0; y < W; ++y) {
                if (fits(tileH, tileW, x, y)) {
                    placeTile(tileH, tileW, x, y, true);
                    if (dfs(idx + 1)) return true;
                    placeTile(tileH, tileW, x, y, false);
                }
            }
        }
        swap(tileH, tileW); // Rotate the tile
    }
    return false;
}

int main() {
    cin >> N >> H >> W;
    tiles.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> tiles[i].first >> tiles[i].second;
    }

    sort(tiles.begin(), tiles.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        return max(a.first, a.second) * min(a.first, a.second) > max(b.first, b.second) * min(b.first, b.second);
    });

    memset(grid, 0, sizeof(grid));
    memset(visited, 0, sizeof(visited));

    if (dfs(0)) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    return 0;
}
