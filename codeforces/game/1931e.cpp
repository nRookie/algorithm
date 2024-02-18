#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;





const int N =2 * 1e6+ 10;


int len[N], zrr[N];
string arr[N];

int n, m;

void build() {

    for (int i = 0; i < n; i ++) {
        len[i] = arr[i].length();
        zrr[i] = 0;
        for (int j = arr[i].size() - 1; j >= 0 && arr[i][j] == '0'; j --) {
            zrr[i] ++;
        }
    }
}

string solve() {
    int ans = 0;
    
    for (int i = 0; i < n; i ++) {
        ans += len[i] - zrr[i];
    }

    sort(zrr, zrr + n);
    reverse(zrr, zrr + n);

    for (int i = 0; i < n; i ++) {
        if (i & 1) ans += zrr[i];
    }

    return ans - 1 >= m ? "Sasha": "Anna";

}
int main() {
    int t; cin >> t;

    while (t --) {
        cin >> n >> m;

        for (int i = 0; i < n; i ++) {
            cin >> arr[i];
        }

        build();

        cout << solve() << '\n';
    }
}