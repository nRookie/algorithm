#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_HW = 10;
int H, W, N;
vector<vector<bool>> grid(MAX_HW, vector<bool>(MAX_HW, false));
vector<pair<int, int>> tiles;

bool canPlaceTile(int row, int col, int height, int width) {
    if (row + height > H || col + width > W) return false;
    for (int i = row; i < row + height; ++i) {
        for (int j = col; j < col + width; ++j) {
            if (grid[i][j]) return false;
        }
    }
    return true;
}

void setTile(int row, int col, int height, int width, bool place) {
    for (int i = row; i < row + height; ++i) {
        for (int j = col; j < col + width; ++j) {
            grid[i][j] = place;
        }
    }
}

bool dfs(int tileIndex) {
    if (tileIndex == N) {
        for (int i = 0; i < H; ++i)
            for (int j = 0; j < W; ++j)
                if (!grid[i][j]) return false;
        return true;
    }

    auto [a, b] = tiles[tileIndex];
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            for (int rot = 0; rot < 2; ++rot) {
                if (canPlaceTile(i, j, a, b)) {
                    setTile(i, j, a, b, true);
                    if (dfs(tileIndex + 1)) return true;
                    setTile(i, j, a, b, false);
                }
                swap(a, b); // Rotate the tile
            }
        }
    }
    if (dfs(tileIndex + 1)) return true;
    
    return false;
}

int main() {
    cin >> N >> H >> W;
    tiles.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> tiles[i].first >> tiles[i].second;
    }

    sort(tiles.begin(), tiles.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.first * a.second > b.first * b.second;
    });

    if (dfs(0)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}
