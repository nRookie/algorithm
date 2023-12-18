#include<iostream>
#include<cstring>
#include<set>
#include<vector>
using namespace std;



const int N = 2 * 1e5 + 10;
typedef pair<int, int> PII;

#define x first
#define y second

PII q[N];
int n;
bool st[N];
int k = 0, km = 0;
int main() {
    cin >> n;
    vector<int> sol;
    for (int i = 0; i < n; i ++) {
        cin >> q[i].x >> q[i].y;
    }
    
    vector<int> myset(n + 1);


    for (int i = n - 1; i >= 0; i --) {
        if (q[i].x == 1) {
            if (myset[q[i].y]  > 0 ) {
                sol.push_back(1);
                myset[q[i].y] -= 1;
                k -=1;
            } else {
                sol.push_back(0);
            }
        } else {
            myset[q[i].y] += 1;
            k += 1;
            km = max(k, km);
        }
    }

    for (auto x: myset) {
        if (x > 0) {
            cout << -1 << endl;
            return 0;
        }
    }

    cout << km << endl;
    for (int i = sol.size() - 1 ; i >= 0 ; i --) {
        cout << sol[i] << " ";
    }
    return 0;
}