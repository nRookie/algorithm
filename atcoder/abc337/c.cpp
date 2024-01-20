#include<iostream>
#include<cstring>
using namespace std;

const int N = 3 * 1e5 +10;

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> A(N), next(N, -1), order;
    int head = -1;

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        if (A[i] == -1) {
            head = i;
        } else {
            next[A[i] - 1] = i;
        }
    }

    for (int i = head; i != -1; i = next[i]) {
        order.push_back(i + 1);
    }
    
    for (int person : order) {
        cout << person << " ";
    }
    cout << endl;

    return 0;
}
