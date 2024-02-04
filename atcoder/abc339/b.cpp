#include<iostream>

using namespace std;

const int N = 110;

int n;

char g[N][N];

int h, w;

int dx[4] = {-1, 0,1, 0};  // up right down, left
int dy[4] = {0, 1, 0, -1 };  //  
int main() {
    cin >> h >> w >> n;
    for (int i = 1; i <= h; i ++)
        for (int j = 1; j <= w; j ++) {
            g[i][j] = '.';
        }

    int x = 1, y = 1;

    int dir = 0; //. white, # black
    while (n -- ) {
        if (g[x][y] == '.') {
            g[x][y] = '#';
            dir = dir + 1;
            dir %= 4;
        } else {
            g[x][y] = '.';
            dir = dir + 3;
            dir %= 4;
        }

        int a = x + dx[dir], b = y + dy[dir];

        if (a <= 0) {
            a = h;
        } 

        else if (b <= 0) {
            b = w;
        }

        else if (a >= h + 1) {
            a = 1;
        }
        else if (b >= w + 1) {
            b = 1;
        }
        x = a, y = b;

        // for (int i = 1; i <= h; i ++) {
        // for (int j = 1; j <=w; j ++) {
        //     cout << g[i][j];
        // }
        // cout << endl;
        // }
        //       cout << endl;
    }

    for (int i = 1; i <= h; i ++) {
        for (int j = 1; j <=w; j ++) {
            cout << g[i][j];
        }
        cout << endl;
    }

    return 0;

    
}