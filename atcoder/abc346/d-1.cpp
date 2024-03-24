#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;

    vector<int> c(n);
    for (int i = 0; i < n; ++i) cin >> c[i];

    vector<vector<vector<int>>> f(n + 1, vector<vector<int>>(2, vector<int>(2, 1e9)));
    f[0][0][0] = f[0][0][1] = 0; // Base case: no cost without any characters

    for (int i = 1; i <= n; ++i) {
        int cost = c[i-1];
        int charInt = s[i-1] - '0';
        for (int j = 0; j < 2; ++j) { // Whether we've formed the pair
            for (int k = 0; k < 2; ++k) { // Last character value
                // Keep the character as is
                int nj = j || (k == charInt); // Becomes 1 if we're forming a pair now
                f[i][nj][charInt] = min(f[i][nj][charInt], f[i-1][j][k]);

                // Change the character
                nj = j || (k != charInt); // Forming a pair if different from the last
                f[i][nj][1-charInt] = min(f[i][nj][1-charInt], f[i-1][j][k] + cost);
            }
        }
    }

    cout << min(f[n][1][0], f[n][1][1]) << endl;

    return 0;
}
