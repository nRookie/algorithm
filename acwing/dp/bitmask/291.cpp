#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;


const int N = 12, M = 1 << N;

int n, m;


// f[i][j] 表示 i - 1 列已经摆好且从第i - 1处到第i列j的所有方案
long long f[N][M];



int main() {
    bool st[M];

    while (cin >> n >> m, n || m) {

        //st统计列内是否存在连续的奇数个0
        for (int i = 0; i < 1 << n; i ++) {
            int cnt = 0;
            bool is_valid = true;

            for (int j = 0; j < n; j ++) {
                if (i >> j & 1) {
                    if (cnt & 1) {
                        is_valid = false;
                        break;
                    }
                    cnt = 0;
                }
                else cnt ++;
            }

            if (cnt & 1) is_valid = false;
            st[i] = is_valid;
        }

        // state[i] 存储从 state[i] 转移的合法状态
        vector<int> state[M];
        // i 对应第i列伸出来的板子
        for (int i = 0; i < 1 << n; i ++) {
            state[i].clear();
            // j 对应 i - 1 列伸出来的板子
            for (int j = 0; j < 1 << n; j ++) {
                //i 和 i - 1 列 没有交集   能被竖着的1x2 小方块塞满， st[i |j] 用来判断列内不存在连续奇数个0
                if ( (i & j) == 0 && st[ i | j])
                    state[i].push_back(j);
            }
        }

        memset(f, 0, sizeof(f));

        f[0][0] = 1;

        for (int i = 1; i <= m; i ++) {
            for (int j = 0; j < 1 << n; j ++) {
                for (auto k : state[j]) {
                    f[i][k] += f[i - 1][j];
                }
            }
        }
        cout<<f[m][0]<<endl;
    }

    return 0;
    
}