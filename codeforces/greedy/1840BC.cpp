#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Lamp {
    int a; // Parameter a_i indicating when the lamp breaks
    int b; // Parameter b_i indicating points received for turning the lamp on
};

// Assuming Lamp is a struct containing integers a and b
void solve() {
    int n;
    cin >> n;
    vector<Lamp> lamps(n);
    for (int i = 0; i < n; ++i) {
        cin >> lamps[i].a >> lamps[i].b;
    }

    // Sort lamps by a_i, then by b_i in descending order if a_i are equal
    sort(lamps.begin(), lamps.end(), [](const Lamp& x, const Lamp& y) {
        return x.a == y.a ? x.b > y.b : x.a < y.a;
    });

    vector<int> breakCounter(n + 1, 0); // to track how many lamps are associated with each break condition,
    int currentlyOn = 0;
    long long totalPoints = 0;

    for (int i = 0; i < n; i ++) {
        if (breakCounter[lamps[i].a] != -1) {
            breakCounter[lamps[i].a] ++;
            currentlyOn++;
            totalPoints += lamps[i].b;
        } 

        if (breakCounter[currentlyOn] != -1) {
            int lampsTobreak = breakCounter[currentlyOn];
            breakCounter[currentlyOn] = -1;
            currentlyOn -= lampsTobreak;
        }
    }

    cout << totalPoints << '\n';
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
