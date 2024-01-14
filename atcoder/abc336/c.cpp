#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

typedef long long ll;

 ll findNthGoodInteger(ll N) {
    ll result = 0;
    ll base = 1;

    while (N > 0) {
        int digit = N % 5;
        result += base * (digit * 2); 

        N /= 5;
        base *= 10;
    }

    return result;
}

int main() {
    ll n;
    cin >> n;

    cout << findNthGoodInteger(n - 1) << "\n";

    return 0;
}