#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    int N;
    cin >> N;
    unordered_map<long long, int> freq;  
    vector<long long> A(N);  
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        freq[A[i]]++;  
    }

    long long total = 0;
    if (freq.count(1)) {
        long long f = freq[1];
        total += f * f * f;
    }


    cout << total << endl;
    return 0;
}
