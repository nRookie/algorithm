#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int K, G, M;

void dfs(int k, int g, int m) {
    if (k == 0) {
        cout << g << " " << m << endl;
        return;
    }
    if (g == G) {
        dfs(k - 1, 0, m);
    } else if (m == 0) {
        dfs(k - 1, g, M);
    } else {
        if (g + m > G) {
            dfs(k - 1, G , g + m - G);
        } else {
            dfs(k - 1, g + m, 0);
        }
    }
}

int main() {
    cin >> K >> G >> M;

    dfs(K, 0, 0);

}