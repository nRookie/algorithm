#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

bool hasIntersection(const vector<pair<int, int>>& chords) {
    set<int> activeEndpoints;

    vector<pair<int, int>> sortedChords = chords;
    sort(sortedChords.begin(), sortedChords.end());

    for (const auto& chord : sortedChords) {
        int A = chord.first;
        int B = chord.second;

        // Check for intersections
        auto it = activeEndpoints.lower_bound(A);
        if (it != activeEndpoints.end() && *it < B) {
            return true; // Intersection found
        }
        activeEndpoints.insert(B);
    }
    return false;
}

int main() {
    int N;
    cin >> N;
    vector<pair<int, int>> chords(N);
    for (int i = 0; i < N; ++i) {
        cin >> chords[i].first >> chords[i].second;
        if (chords[i].first > chords[i].second) {
            swap(chords[i].first, chords[i].second);
        }
    }

    if (hasIntersection(chords)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}
