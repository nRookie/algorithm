#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <iomanip>
using namespace std;

string s;


int main() {

    int n, d, x;

    // an array to store the weights of each item
    long double w[15];

    // A variable to store the average weight of the items when equally distributed among the lucky bags.
    long double ave = 0;

    // A 2D array for dynamic programming. The first dimension represents subsets of items, encoded as bitmasks, 
    // and the second dimension represents the number of bags used.
    long double dp[(1<< 15)][16];

    // 
    long double total_weight_of_items_in_the_subset;

    cin >> n >> d;

    for (int i = 0; i < n; i ++) 
        cin >> w[i], ave += w[i];

    ave/= ((long double)d);

    for (int i = 0; i < (1 << n); i ++) {
        total_weight_of_items_in_the_subset = 0;


        for (int j = 0; j < n; j ++) {
            if (i &(1<<j)) total_weight_of_items_in_the_subset+= w[j];
        }
        // The line dp[i][1] = pow(total_weight_of_items_in_the_subset - ave, 2); 
        // in the code is calculating the variance for a specific subset of items when all those items are placed in a single lucky bag.
        dp[i][1] = pow(total_weight_of_items_in_the_subset-ave, 2);
        for (int bag = 2; bag <= d; bag ++) {
            dp[i][bag] = dp[i][bag - 1] + dp[0][1];
            x = i;

            // The loop's purpose is to explore all possible ways of distributing a subset of items into one bag and the remaining items into other bags.
            while (x > 0) {
                dp[i][bag] = min(dp[i][bag], dp[i - x][bag - 1] + dp[x][1]);
                x = (x - 1) & i;
            }
        }
    }

    cout << setprecision(10) << (dp[(1 << n) - 1][d]/((long double)d)) << endl;
    
    return 0;
}