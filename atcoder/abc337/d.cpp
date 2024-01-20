#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

int main()
{
    int H, W, K;
    cin >> H >> W >> K;
    vector<string> grid(H);
    for (int i = 0; i < H; ++i)
    {
        cin >> grid[i];
    }

    int min_operations = INT_MAX;
    vector<vector<int>> prefix_rows(H, vector<int>(W + 1, 0)), prefix_cols(W, vector<int>(H + 1, 0));

    for (int i = 0; i < H; ++i)
    {
        for (int j = 0; j < W; ++j)
        {
            prefix_rows[i][j + 1] = prefix_rows[i][j] + (grid[i][j] == '.');
            prefix_cols[j][i + 1] = prefix_cols[j][i] + (grid[i][j] == '.');
        }
    }

    for (int i = 0; i < H; ++i)
    {
        int x_count = 0;
        for (int j = 0; j < K; ++j)
        {
            if (grid[i][j] == 'x')
            {
                x_count++;
            }
        }
        if (x_count == 0)
        {
            int ops = prefix_rows[i][K] - prefix_rows[i][0];
            min_operations = min(min_operations, ops);
        }

        for (int j = 1; j <= W - K; ++j)
        {
            if (grid[i][j - 1] == 'x')
                x_count--;
            if (grid[i][j + K - 1] == 'x')
                x_count++;

            if (x_count == 0)
            {
                int ops = prefix_rows[i][j + K] - prefix_rows[i][j];
                min_operations = min(min_operations, ops);
            }
        }
    }

    for (int j = 0; j < W; ++j)
    {
        int x_count = 0; 
        for (int i = 0; i < K; ++i)
        {
            if (grid[i][j] == 'x')
            {
                x_count++;
            }
        }
        if (x_count == 0)
        {
            int ops = prefix_cols[j][K] - prefix_cols[j][0];
            min_operations = min(min_operations, ops);
        }

        for (int i = 1; i <= H - K; ++i)
        {
            if (grid[i - 1][j] == 'x')
                x_count--;
            if (grid[i + K - 1][j] == 'x')
                x_count++;

            if (x_count == 0)
            {
                int ops = prefix_cols[j][i + K] - prefix_cols[j][i];
                min_operations = min(min_operations, ops);
            }
        }
    }

    if (min_operations == INT_MAX)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << min_operations << endl;
    }

    return 0;
}
