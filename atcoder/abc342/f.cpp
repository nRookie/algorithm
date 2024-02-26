#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

double solve(int N, int L, int D) {
    // Probability of not exceeding N when stopping
    vector<double> p(N + 1, 0.0);
    p[0] = 1.0; // Starting point, probability of 0 is 1

    // Calculate probability distribution for x
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= D; ++j) {
            if (i - j >= 0) {
                p[i] += p[i - j] / D;
            }
        }
    }

    // Sum probabilities to get cumulative distribution for better performance in later calculations
    vector<double> cumulative(N + 2, 0.0);
    for (int i = 1; i <= N + 1; ++i) {
        cumulative[i] = cumulative[i - 1] + p[i - 1];
    }

    double ans = 0.0;
    vector<double> q(N + 2, 0.0); // Probability distribution for y, with an extra space for simplification
    q[0] = 1.0; // Starting point

    // Calculate probability distribution for y
    for (int i = 1; i <= N + 1; ++i) {
        q[i] = 0.0;
        for (int j = 1; j <= D; ++j) {
            if (i - j >= 0) {
                q[i] += q[i - j] / D;
            }
        }
        if (i <= L) {
            // The dealer must continue rolling until y < L
            q[i] = 0;
        }
        if (i <= N) {
            // Calculate the winning probability for each value of x
            ans += p[i] * (cumulative[N + 1] - cumulative[i + 1]);
        } else {
            // If y > N, add the probability of this event
            ans += q[i];
        }
    }

    return ans;
}

int main() {
    int N, L, D;
    cin >> N >> L >> D;

    double result = solve(N, L, D);

    cout << fixed << setprecision(12) << result << endl;
    return 0;
}
