#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

string canChooseElements(int n, int m, int k, vector<int>& a, vector<int>& b) {
    unordered_set<int> uniqueA, uniqueB, common;
    // Fill the sets based on the occurrence of elements from 1 to k
    for (int i = 0; i < n; i++) {
        if (a[i] <= k) {
            uniqueA.insert(a[i]);
        }
    }
    for (int i = 0; i < m; i++) {
        if (b[i] <= k) {
            if (uniqueA.find(b[i]) == uniqueA.end() && common.find(b[i]) == common.end()) { // Not found in A and not common
                uniqueB.insert(b[i]);
            } else if (uniqueA.find(b[i]) != uniqueA.end()) { // Found in A, move to common
                common.insert(b[i]);
                uniqueA.erase(b[i]);
            }
        }
    }

    // Applying the conditions
    if (uniqueA.size() > k / 2 || uniqueB.size() > k / 2 || (uniqueA.size() + uniqueB.size() + common.size() < k)) {
        return "NO";
    } else {
        return "YES";
    }
}

int main() {
    int t, n, m, k;
    cin >> t;
    while (t--) {
        cin >> n >> m >> k;
        vector<int> a(n), b(m);
        for (int& ai : a) cin >> ai;
        for (int& bi : b) cin >> bi;
        cout << canChooseElements(n, m, k, a, b) << endl;
    }
    return 0;
}
