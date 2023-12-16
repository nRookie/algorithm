#include<iostream>
#include<cstring>
#include<set>
using namespace std;



const int N = 2 * 1e5 + 10;
typedef pair<int, int> PII;

#define x first
#define y second

PII q[N];
int n;
bool st[N];
int main() {
    cin >> n;

    for (int i = 0; i < n; i ++) {
        cin >> q[i].x >> q[i].y;
    }

    set<int> myset;
    for (int i = n - 1; i >= 0; i --) {
        if (q[i].x == 2) {
            myset.insert(q[i].y);
        } else {
            if(myset.count(q[i].y)) {
                myset.erase(q[i].y);
                st[i] = true;
            }
        }
    }

    for (int i = 0; i < n; i ++) {
        cout << st[i] << " ";
    }
    cout << endl;
    return 0;
}