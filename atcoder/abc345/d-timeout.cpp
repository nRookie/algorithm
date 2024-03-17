#include <iostream>
#include <vector>
using namespace std;

bool canPlaceTiles(int H, int W, vector<vector<bool>>& grid, vector<pair<int, int>>& tiles, int idx) {
    if (idx == tiles.size()) {
        for (int i = 0; i < H; ++i)
            for (int j = 0; j < W; ++j)
                if (!grid[i][j]) return false;
        return true;
    }

    auto [a, b] = tiles[idx];
    for (int rot = 0; rot < 2; ++rot) {
        swap(a, b);
        for (int i = 0; i <= H - a; ++i) {
            for (int j = 0; j <= W - b; ++j) {
                bool canPlace = true;
                for (int x = 0; x < a && canPlace; ++x)
                    for (int y = 0; y < b; ++y)
                        if (grid[i + x][j + y]) {
                            canPlace = false;
                            break;
                        }

                if (canPlace) {
                    for (int x = 0; x < a; ++x)
                        for (int y = 0; y < b; ++y)
                            grid[i + x][j + y] = true;

                    if (canPlaceTiles(H, W, grid, tiles, idx + 1)) return true;

                    for (int x = 0; x < a; ++x)
                        for (int y = 0; y < b; ++y)
                            grid[i + x][j + y] = false;
                }
            }
        }
    }

    return canPlaceTiles(H, W, grid, tiles, idx + 1); 
}

int main() {
    int N, H, W;
    cin >> N >> H >> W;
    vector<pair<int, int>> tiles(N);
    for (int i = 0; i < N; ++i) {
        cin >> tiles[i].first >> tiles[i].second;
    }

    vector<vector<bool>> grid(H, vector<bool>(W, false));
    if (canPlaceTiles(H, W, grid, tiles, 0)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
