#include<iostream>
using namespace std;

const int N = 10;

char a[N][N];


int n, m;
int stone = 0;
bool res = false;
void dfs(int x, int y, int u) {

    if (x >= n || y>= m) return;
    if (a[x][y] == '#') {
        u ++;
        // printf("x: %d y: %d \n", x, y);
        if (x == n - 1 && y == m -1) {
            if (u == stone) {
                res = true;
            }

            //cout <<"get end stone: " << stone <<" u: " << u << endl;
            return ;
        }

        dfs(x + 1, y, u);
        dfs(x, y + 1, u);
    }
}

int main() {
    // left, up, right, down.

    cin >> n >> m;

    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            cin >> a[i][j];
            if (a[i][j] == '#') stone++;
        }
    }

    dfs(0,0,0);

    if (res) cout <<"Possible" << endl;
    else cout << "Impossible" << endl;

    return 0;
    
}