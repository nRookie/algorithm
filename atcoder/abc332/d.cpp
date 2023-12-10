#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

int n, m;
string s;

bool row[6];
bool column[6];
int a[6][6];
int b[6][6];

unordered_map<int,int > As; 


string swapRows(const string& state, int row, int cols) {
    string newState = state;
    for (int i = 0; i < cols; ++i) {
        swap(newState[row * cols + i], newState[(row + 1) * cols + i]);
    }
    return newState;
}

string swapColumns(const string& state, int col, int rows, int cols) {
    string newState = state;
    for (int i = 0; i < rows; ++i) {
        swap(newState[i * cols + col], newState[i * cols + col + 1]);
    }
    return newState;
}
int bfs(const string& start, const string& end, int rows, int cols) {
    queue<string> q;
    unordered_map<string, int> distance;

    q.push(start);
    distance[start] = 0;

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        if (current == end) return distance[current];

        for (int i = 0; i < rows - 1; ++i) {
            string newState = swapRows(current, i, cols);
            if (!distance.count(newState)) {
                distance[newState] = distance[current] + 1;
                q.push(newState);
            }
        }

        for (int i = 0; i < cols - 1; ++i) {
            string newState = swapColumns(current, i, rows, cols);
            if (!distance.count(newState)) {
                distance[newState] = distance[current] + 1;
                q.push(newState);
            }
        }
    }
    return -1;
}

int main() {
    cin >> n >> m;

    string end;

    string start;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1;j <= m; j ++) {
            cin >> a[i][j];
            As[a[i][j]] ++;
            start += a[i][j] - '0';
        }
    }
    for (int i = 1; i <= n; i ++) {
        for (int j = 1;j <= m; j ++) {
            cin >> b[i][j];
            end += (b[i][j] - '0');
            if (As.count(b[i][j])) {
                if (b[i][j] == 0) {
                    cout << -1 << endl;
                    return 0;
                }
                As[b[i][j]] --;
            } else {
                cout << -1 << endl;
                return 0;
            }
        }
    }

    cout << bfs(start, end, n, m) << endl;

    return 0;
}