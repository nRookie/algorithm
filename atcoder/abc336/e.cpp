#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

typedef long long ll;

// Dynamic programming table
// dp[digitIndex][isLessThanN][sumOfDigits][remainder]
ll dp[20][2][130][130];

int main() {
    ll n;
    cin >> n;
    n++; // Increment to include N itself if it's a good integer

    // Break the number into its individual digits
    vector<int> digits;
    while (n) {
        digits.push_back(n % 10);
        n /= 10;
    }
    reverse(digits.begin(), digits.end());

    int numDigits = digits.size();
    ll totalGoodIntegers = 0;

    // Iterate over all possible sums of digits
    for (int sumLimit = 1; sumLimit <= 126; sumLimit++) {
        // Initialize DP table
        for (int i = 0; i <= numDigits; i++) {
            for (int isLess = 0; isLess < 2; isLess++) {
                for (int sum = 0; sum <= sumLimit; sum++) {
                    for (int remainder = 0; remainder < sumLimit; remainder++) {
                        dp[i][isLess][sum][remainder] = 0;
                    }
                }
            }
        }

        // Base case
        dp[0][0][0][0] = 1;

        // Build the table
        for (int i = 0; i < numDigits; i++) {
            for (int isLess = 0; isLess < 2; isLess++) {
                for (int sum = 0; sum <= sumLimit; sum++) {
                    for (int remainder = 0; remainder < sumLimit; remainder++) {
                        for (int d = 0; d < 10; d++) {
                            int nextIndex = i + 1;
                            int nextIsLess = isLess;
                            int nextSum = sum + d;
                            int nextRemainder = (remainder * 10 + d) % sumLimit;

                            if (nextSum > sumLimit) continue;
                            if (isLess == 0) {
                                if (digits[i] < d) continue;
                                if (digits[i] > d) nextIsLess = 1;
                            }

                            dp[nextIndex][nextIsLess][nextSum][nextRemainder] += dp[i][isLess][sum][remainder];
                        }
                    }
                }
            }
        }

        // Accumulate the count of good integers
        totalGoodIntegers += dp[numDigits][1][sumLimit][0];
    }

    cout << totalGoodIntegers << endl;

    return 0;
}
