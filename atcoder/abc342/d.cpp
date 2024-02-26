#include<iostream>
#include<vector>
#include<cmath>
#include<map>
using namespace std;

map<int, int> factorize(int n) {
    map<int, int> factors;
    for (int i = 2; i * i <= n; ++i) {
        while (n % i == 0) {
            factors[i]++;
            n /= i;
        }
    }
    if (n > 1) factors[n]++;

    for (auto & p : factors) {
         cout << p.first << " " << p.second << endl;
    }
    return factors;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    map<map<int, int>, int> freq;  
    int zeroCount = 0;  

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] == 0) {
            zeroCount++;
            continue;
        }
        auto factors = factorize(a[i]);
        map<int, int> oddFactors;  
        for (auto& p : factors) {
            if (p.second % 2 == 1) {
                oddFactors[p.first] = 1;
            }
        }
        freq[oddFactors]++;
    }
    // 3 * 3 * 2
    // 18

    // 3 * 3* 2 * 2 * 2

    // 72

    // 18 * 7 2

    long long count = 0;
 
    for (auto& p : freq) {
        long long k = p.second;
        count += k * (k - 1) / 2;
    }
 
    count += zeroCount * (long long)(n - zeroCount) + (zeroCount * (long long)(zeroCount - 1) / 2);

    cout << count << endl;
    return 0;
}
