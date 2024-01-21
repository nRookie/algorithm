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

    // Iterate through each element
    for (int i = 1; i < n - 1; i++) {
        for (int d = -9; d <= 9; d++) {
            int aj = a[i] - d;
            int ak = a[i] + d;
            printf("i: %d    d: %d \n", i, d);
            if (aj >= 1 && aj <= 10 && ak >= 1 && ak <= 10) {
                // Count valid positions for aj and ak
                int leftCount = 0, rightCount = 0;
                for (int pos : position[aj]) {
                    if (pos < i) {
                        printf("pos: %d, i %d, %d < %d\n", pos, i, aj ,a[i]);
                        leftCount++;
                    }
                }
                for (int pos : position[ak]) {
                    if (pos > i) {
                    printf("pos: %d, i %d, %d > %d\n", pos, i, ak ,a[i]);
                        rightCount++;
                    }

                }
                count += leftCount * rightCount;
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
