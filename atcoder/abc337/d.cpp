#include <iostream>
#include <vector>
#include <string>
#include<climits>
#include <algorithm>

using namespace std;

bool isPossible(const vector<string>& grid, int H, int W, int K, int operations) {
    for (int i = 0; i < H; ++i) {
        int dotCount = 0, xCount = 0;
        for (int j = 0; j < W; ++j) {
            if (j >= K) {
                if (grid[i][j - K] == '.') dotCount--;
                if (grid[i][j - K] == 'x') xCount--;
            }
            if (grid[i][j] == '.') dotCount++;
            if (grid[i][j] == 'x') xCount++;

            if (j >= K - 1 && xCount == 0 && dotCount <= operations)
                return true;
        }
    }

    for (int j = 0; j < W; ++j) {
        int dotCount = 0, xCount = 0;
        for (int i = 0; i < H; ++i) {
            if (i >= K) {
                if (grid[i - K][j] == '.') dotCount--;
                if (grid[i - K][j] == 'x') xCount--;
            }
            if (grid[i][j] == '.') dotCount++;
            if (grid[i][j] == 'x') xCount++;

            if (i >= K - 1 && xCount == 0 && dotCount <= operations)
                return true;
        }
    }

    return false;
}


int main() {
    int H, W, K;
    cin >> H >> W >> K;
    vector<string> grid(H);
    for (int i = 0; i < H; ++i) {
        cin >> grid[i];
    }


   
   int low = 0, high = K, ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (isPossible(grid, H, W, K, mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    cout << ans << endl;
}
