#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 7;
const int MAX_H = 10;
const int MAX_W = 10;

int n, h, w;
vector<int> a(MAX_N);
vector<int> b(MAX_N);
vector<vector<int>> c(MAX_H, vector<int>(MAX_W, -1));
bool ans;

void solve(int unused, int curi, int curj) {
    bool can;

    while(c[curi][curj] >= 0) {
        curj ++;
        if (curj >= w) {
            curi++;
            curj = 0;
        }

        if (curi >= h)
            break;
    }

    if (curi >= h) {
        ans = true;
        return;
    }

    for (int i = 0; i < n;  i ++)
        if(unused & (1 << i)) {
            can = true;
            for (int ii = 0; ii < a[i]; ++ii) 
                for (int jj = 0; jj < b[i]; ++jj) 
                    if (curi + ii < h  && curj + jj < w)  
                        if (c[curi + ii][curj + jj] < 0)
                            c[curi + ii][curj + jj] = i;
                        else can = false;
                    else can = false;
            if (can)
                solve(unused ^ (1 << i), curi, curj);
            
            for (int ii = 0; ii < a[i]; ii ++)
                for (int jj = 0; jj < b[i]; jj ++) 
                    if ( curi + ii < h && curj + jj < w)
                        if (c[curi + ii][curj + jj] == i)
                            c[curi + ii][curj + jj] = - 1;
            
            if (a[i] != b[i]) {
                can = true;
                for (int ii = 0; ii < b[i] ; ii ++)
                    for (int jj = 0; jj < a[i]; jj++)
                        if (curi + ii < h && curj + jj < w) 
                            if (c[curi + ii][curj + jj] < 0)
                                c[curi + ii][curj + jj] = i;
                            else can = false;
                        else can = false;
                
                if (can) solve (unused ^ (1 << i) , curi, curj);
                for (int ii = 0; ii < b[i] ; ii ++)
                    for (int jj = 0; jj < a[i]; jj++) 
                        if ( curi + ii < h && curj + jj < w) 
                            if (c[curi + ii][curj + jj] == i)
                                c[curi + ii][curj + jj] = -1;
                
            }
        }
        
}
int main() {
    cin >> n >> h >> w;
    for (int i = 0; i < n; ++i)
        cin >> a[i] >> b[i];
    for (int i = 0; i < h; ++i)
        for (int j = 0; j < w; ++j)
            c[i][j] = -1;
    ans = false;
    solve((1 << n) - 1, 0, 0);
    if (ans)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    return 0;
}
