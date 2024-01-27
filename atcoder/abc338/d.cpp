#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


typedef long long ll;
int main() {
    int N, M;
    cin >> N >> M;

    vector<int> X(M);
    for (int i = 0; i < M; ++i) {
        cin >> X[i];
        --X[i]; // Adjusting to 0-based indexing
    }

    vector<ll> v(N, 0);
    vector<ll> diff( N + 1, 0);
    auto add = [&](int l, int r, int v) {
        if (l > r) return ;
        diff[l] += v;
        diff[r + 1] -= v;
    };

    diff[0] = v[0];

    for (int i = 1; i < N; i ++) {
        diff[i] = v[i] - v[i - 1];
    }


    for (int i = 0; i < M - 1; ++i) {
        int a = X[i];
        int b = X[i + 1];

        if (a == b) continue; // No movement needed if a and b are the same

        if (a > b) swap(a, b); // Ensure a is less than b

        int clockwiseDistance = b - a;
        int counterclockwiseDistance = N - clockwiseDistance;

        // Update v for bridges in the clockwise path
        // for (int j = a; j < b; ++j) {
        //     v[j] += counterclockwiseDistance;
        // }

        add(a, b - 1, counterclockwiseDistance);

        // // Update v for bridges in the counterclockwise path
        // for (int j = b; j != a; j = (j + 1) % N) {
        //     v[j] += clockwiseDistance;
        // }
        add (b, N, clockwiseDistance);
        if (a != 0)
        add (0, a - 1, clockwiseDistance);
    }
    v[0] = diff[0];
    for (int i = 1; i < N; i ++) {
        v[i] = diff[i] + v[i - 1];
    }

    // Find the minimum value of v
    ll answer = *min_element(v.begin(), v.end());
    std::cout << answer << endl;

    return 0;
}
