#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int countGoodPairs(const vector<int>& a) {
    int n = a.size();
    int count = 0;
    unordered_map<int, vector<int>> position;

    // Store positions of each element
    for (int i = 0; i < n; i++) {
        position[a[i]].push_back(i);
    }


    for (auto& pair : position) {
        // Sort each vector
        sort(pair.second.begin(), pair.second.end());
    }
    // Iterate through each element
    for (int i = 1; i < n - 1; i++) {
        for (int d = -9; d <= 9; d++) {
            int aj = a[i] - d;
            int ak = a[i] + d;
            printf("i: %d    d: %d \n", i, d);
            if ( aj >= 1 && aj <= 10 && ak >= 1 && ak <= 10) {
                // Count valid positions for aj and ak
                int l = 0, r =  position[aj].size();

                cout << l << " " << r << " l and r" << endl;
                int target = i;
                while (l < r) {
                    int mid = l + r >> 1;
                    // i  mid          mid = 3
                    // 1 2 3 4 5 6     target = 2;
                    if (target <= position[aj][mid]) {
                        r = mid;
                    } else {
                        l = mid + 1;
                    }
                }
                int left = 0;
      
                if (target > position[aj][l]) {
                    left ++;
                }
                l = 0, r =  position[ak].size();
                while (l < r) {
                    int mid = (l + r + 1) >> 1;
                    // i  mid          mid = 3
                    // 1 2 3 4 5 6     target = 2;
                    if (target < position[ak][mid]) {
                        r = mid - 1;
                    } else {
                        l = mid;
                    }
                }
 
                int right = 0;
                if (target < position[ak][l]) {
                    right ++;
                }
                count += left * right;
                cout << "count is " << count << endl;
            }
        }
    }
    return count;
}

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    cout << countGoodPairs(A) << endl;

    return 0;
}




// 5
// 5 3 4 1 5

// sample output
// 3

// There are three good pairs: 
// (l,r)=(1,4),(1,5),(2,5).

// (A1,A2,A3,A4) contains an arithmetic subsequence of length 
// 3, which is (5,3,1), so (1,4) is a good pair.

// 1 2 4

// (A1,A2,A3,A4, A5) contains an arithmetic subsequence of length 
// 3, which is (5,3,1), (3,4,5) so (1,5) is a good pair.

// (A2,A3,A4,A5) contains an arithmetic subsequence of length 
// 3, which is  (3,4,5) so (2,5) is a good pair.