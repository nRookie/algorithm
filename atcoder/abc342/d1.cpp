#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;



map<int,int> factorize(int n) {
    map<int,int> factors;
    for (int i = 2; i * i <= n; i ++) {
        while(n % i == 0) {
            factors[i] ++;
            n /= i;
        }
    }
    if (n > 1) factors[n] ++;
    return factors;
}

int main() {
    int n;

    cin >> n;

    map <map<int, int> , int> freq;
    int zeros = 0;
    for (int i = 0; i < n; i ++) {
        int a ;
        cin >> a;

        if (a == 0) {
            zeros ++;
            continue;
        }
        auto factors = factorize(a);

        map<int, int> oddFactors;

        for (auto & p : factors) {
            if ((p.second & 1) == 1) {
                oddFactors[p.first] = 1;
            }
        }

        freq[oddFactors] ++;
    }

    long long count = 0;
    for (auto odds : freq) {
        int k = odds.second;
        count += k * (k - 1) / 2;
    }

    count += zeros * (long long)(n - zeros) +  (long long )zeros * (zeros - 1) / 2;

    cout << count << endl;
}