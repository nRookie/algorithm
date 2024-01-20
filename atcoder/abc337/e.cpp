#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


// at least one bottle has poison
int main() {
    int N;
    cin >> N;

    int M = ceil(log2(N));
    cout << M << endl;
    fflush(stdout);
    for (int i = 0; i < M; ++i) {
        vector<int> bottles;
        for (int j = 1; j <= N; ++j) {
            if (j & (1 << i)) {
                bottles.push_back(j);
            }
        }

        cout << bottles.size();
        for (int bottle : bottles) {
            cout << " " << bottle;
            fflush(stdout);
        }
        cout << endl;
        fflush(stdout);
    }

    string responses;
    cin >> responses;

    int spoiled = 0;
    for (int i = 0; i < M; i++) {
        if (responses[i] == '1') {
            spoiled |= (1 << i);
        }
    }

    if(!spoiled) cout << N;

    else cout << spoiled << endl;

 
    fflush(stdout);

    return 0;
}
