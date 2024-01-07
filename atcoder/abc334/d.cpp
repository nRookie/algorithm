#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;




bool check(vector<long long> &pre, long long n, long long X) {
    // X reindeer.
    // cout << n << " " << pre[n] << " " << X << endl;
    if (pre[n] <= X) {
        return true;
    } else {
        return false;
    }

}
int main() {
    long long n, m;
    cin >> n >> m;

    vector<long long> a(n);
    vector<long long> pre(n + 1);

    for (long long i = 0; i < n;i ++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    // cout << endl;
    for (long long i = 1; i <= n; i ++) {
        pre[i] = pre[i - 1] + a[i - 1];
    }

    // cout << endl;
    // for (long long i = 1; i <= n; i ++) {
    //     cout << pre[i] << " ";
    // }
    // cout << endl;
    while(m -- ) {
        long long X = 0;
        cin >> X;
        long long l = 0, r = n;

        while(l < r) {
            long long mid = l + r + 1 >> 1;
            // cout << mid << endl;
            if (check(pre, mid, X)) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }

        cout << r << endl;
    }

    return 0;
}


// 1 2 3 4
// 