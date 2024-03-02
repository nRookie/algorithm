#include <iostream>
#include <vector>
using namespace std;

pair<int, int> findSwapIndices(const vector<int>& p) {
    int n = p.size();
    int idx1 = -1, idx2 = -1, idxN = -1;

    // Find indices of 1, 2, and n
    for (int i = 0; i < n; ++i) {
        if (p[i] == 1) idx1 = i;
        else if (p[i] == 2) idx2 = i;
        else if (p[i] == n) idxN = i;
    }

    // Determine the swap to minimize permutation subarrays
    if (idxN > idx1 && idxN < idx2) return {idx1 + 1, idx2 + 1}; // Swap 1 and 2
    if (idxN < idx1 && idxN < idx2) return idx1 < idx2 ? make_pair(idxN + 1, idx1 + 1) : make_pair(idxN + 1, idx2 + 1); // Swap n with the first of 1 and 2
    if (idxN > idx1 && idxN > idx2) return idx1 > idx2 ? make_pair(idxN + 1, idx1 + 1) : make_pair(idxN + 1, idx2 + 1); // Swap n with the last of 1 and 2

    // If none of the conditions match, no swap is needed (should not happen)
    return {1, 1}; // This is just to satisfy the function return type
}



// in between  1 3 5 4 2


// 5  3   1   4  2

// 1 3 5 4 2

//1  3 2 4 5
//

pair<int, int> solve() {
    int n ;

    cin >> n;

    vector<int> p(n + 1);

    for (int i = 1; i <= n; i ++) cin >> p[i];

    int idx1 = -1, idx2 = -1, idxn = -1;

    for (int i = 1; i <=n ; i ++ ) {
        if (p[i] == 1) idx1 = i;
        if (p[i] == 2) idx2 = i;
        if (p[i] == n) idxn = i;
    }

    //if (idx1 < idxn && idxn < idx2) return make_pair(idx1, idx2);
    if (idx1 < idxn && idx2 < idxn) {
        if (idx1 < idx2) {
            return make_pair(idx2, idxn);
        } else {
            return make_pair(idx1, idxn);
        }
    }
    if (idx1 > idxn && idx2 > idxn) {
        if (idx1 < idx2) {
            return make_pair(idx1, idxn);
        } else {
            return make_pair(idx2, idxn);
        }
    }

    return make_pair(1,1);
}



int main() {
    int t;
    cin >> t;
    while (t--) {

        auto [i, j] = solve();
        cout << i << " " << j << "\n";
    }
    return 0;
}
