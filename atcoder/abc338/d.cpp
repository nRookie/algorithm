#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> tour(M);
    for (int i = 0; i < M; ++i) {
        cin >> tour[i];
        tour[i]--;  // Convert to zero-based index
    }

    // Function to calculate the direct distance between two islands
    auto directDistance = [&](int i, int j) {
        return min(abs(i - j), N - abs(i - j));
    };

    // Calculate the total distance of the tour
    int totalDistance = 0;
    for (int i = 0; i < M - 1; ++i) {
        totalDistance += directDistance(tour[i], tour[i + 1]);
    }

    // Find the minimum possible length of the tour with one bridge closed
    int minLength = totalDistance;
    for (int i = 0; i < M - 1; ++i) {
        int save = directDistance(tour[i], tour[i + 1]);  // Distance saved by closing a bridge
        int additional = directDistance(tour[i], (tour[i + 1] + 1) % N) + 1; // Additional distance due to bridge closure

        minLength = min(minLength, totalDistance - save + additional);
    }
    // Check the closing of the bridge between the last and first island in the tour
    minLength = min(minLength, totalDistance - directDistance(tour[M - 1], tour[0]) + directDistance(tour[M - 1], (tour[0] + 1) % N) + 1);

    cout << minLength << endl;

    return 0;
}
