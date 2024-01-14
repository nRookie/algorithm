#include <iostream>
#include <vector>

using namespace std;


int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int& x : A) cin >> x;

    vector<int> left(N), right(N);

    for (int i = 0; i < N; ++i) {
        if (i == 0) left[i] = min(A[i], 1);
        else left[i] = min(A[i], left[i - 1] + 1);
    }

    for (int i = N - 1; i >= 0; --i) {
        if (i == N - 1) right[i] = min(A[i], 1);
        else right[i] = min(A[i], right[i + 1] + 1);
    }

    // Find the maximum pyramid size
    int maxSize = 0;
    for (int i = 0; i < N; ++i) {
        int height = min(left[i], right[i]);
        maxSize = max(maxSize, height);
    }

    cout << maxSize << endl;
    return 0;
}



// 2,2,3,1,1
// 1,2,3,1,1
// 1,2,2,1,1