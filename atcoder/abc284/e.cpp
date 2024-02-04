#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int N = 1e6 + 10, M = 4 * N + 10;

int h[N], e[M], ne[M], idx;

const int MAX = 1000000;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

bool st[N]; // Use bool instead of int for state array
int path;

void dfs(int u) {
    if (path >= MAX) return;
        st[u] = true;
        path++;
        for (int i = h[u]; ~i; i = ne[i]) {
            int j = e[i];
            if (!st[j]) { // Only proceed if the next node hasn't been visited
                dfs(j);
            }
        }
        st[u] = false; // Reset state for u, to allow revisiting in a different path
}

int n, m;
int main() {
    cin >> n >> m;

    memset(h, -1, sizeof h);

    while (m--) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        add(b, a);
    }

    // Reset the state array and start DFS from vertex 1
    memset(st, 0, sizeof st);
    path = 0;
    dfs(1);

    cout << min(path, MAX) << endl; // Print the minimum of path and MAX
    return 0;
}
