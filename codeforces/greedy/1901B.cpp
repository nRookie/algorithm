#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;



const int N = 2* 1e6 + 10, M = 4 * N;

typedef pair<int,int> PII;
int h[N], ne[M], e[M], w[M], idx;

void add (int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}


typedef long long ll;
ll exgcd(ll a, ll b, ll & x, ll&  y) {
    
        if (b == 0) {
            x = 1;
            return a;
        }
        ll d = exgcd(b, a % b, y , x);
        y -= a/b * x;  
        
        return d;
}



// ribbon to n celss.
// 1 to n from left to right
// initially. an integer 0 is written in each cell.

// 
// chip in the 1-st cell of the ribbon,
// one of the two following actions

// 1.  move the chip to the next cell (at, i, move to i + 1) , this action is impossible if the chip is in the last cell.


// 2. choose any cell x and teleport the chip into that cell. It is possible to choose the cell where the chip is currently located.

// at the end of each turn, the integer written in the cell with the chip is increased by 1.

// Monocarp's goal is to make some turns so that the 1-st cell contains the integer c1, the 2nd cell contains c2... n-th cell contains the integer cn.
// He want's to teleport the chip as few time as possible.


// Help Monocarp calculate the minimum number of times he has to teleport the chip.


void solve() {
    int n;
    cin >> n;
    vector<int> c(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> c[i];
    }
    ll res = 0;
    int maxx = 0;
    int diff = 0;
    // for (int i = 0; i < n; i ++) {
    //     if (c[i] < c[i + 1]) {
    //         maxx = max(maxx, c[i]);
    //     } else {
    //         res += maxx - diff;
    //         maxx = 0;
    //         diff = c[i + 1];
    //     }
    // }
    // res += maxx - diff;


    for (int i = 0; i < n; i ++) {
        if (c[i] <= c[i + 1]) {
            maxx = max(maxx, c[i + 1]);
        } else {
            res += maxx - diff;
            maxx = c[i + 1];
            diff = c[i + 1];
        }
    }
    res += maxx - diff;

    //  4 1 2 3 4 1 2 3 4         res   maxx   diff       res maxx diff

    // 0 4 1 2 3 4 1 2 3 4                
    // i                            0    4       0               
    //   i                                                 4    1    1
    //     i                        4    2       1
    //       i                      4    3       1
    //         i                    4    4       1
    //           i                                         7    1    1
    //             i                7    2       1                       
    //               i              7    3       1
    //                 i            7    4       1                      
    cout << res - 1 << endl;

}



int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}