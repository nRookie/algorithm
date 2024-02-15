#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
#include<vector>
using namespace std;


const int N = 10100;

int a[N];
int f[N];
int main() {
    
   int n = 1;
    
   while(cin >> a[n]) n ++; 
   int res = 0;
   memset(f, 0, sizeof f);

    for (int i = 1; i < n; i ++) {
        f[i] = 1;
        for (int j = 1; j < i; j ++) {
            if (a[j] >= a[i]) {
                f[i] = max(f[i], f[j] + 1);
            }
        }
        res = max(res, f[i]);
    }
    cout << res << endl;
    priority_queue<int, vector<int>, greater<int>> heap1;
    int res2 = 0;
    for (int i = 1; i < n; i ++) {
        vector<int> backup;
        while(heap1.size()) {
            int t = heap1.top();
            heap1.pop();
            if (t >= a[i]) {
                t = a[i];
                heap1.push(t);
                break;
            } else {
                backup.push_back(t);
            }
        }

        if (heap1.size() == 0) {
            res2 ++;
            heap1.push(a[i]);
        }
        for (auto v : backup) heap1.push(v);
    }

    cout <<res2 << endl;
    
    return 0;
}