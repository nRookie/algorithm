#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        vector<int> A(5), P(5);
        long long total = 0;
        for (int &a : A) {
            cin >> a; 
            total += a;
        }
        for (int &p : P) {
            cin >> p;  
        }

        long long needed = 15 - total;

        if (needed <= 0) {
            cout << 0 << endl;
            continue ;
        }

        
        vector<pair<long long, int>> cost;

        for (int i = 0; i < 5; i ++) {
            cost.push_back({P[i], i + 1});
        }
    
        // a.first / a.second > b.first > b.second
        // all / count =  
        sort(cost.begin(), cost.end(), []( pair<long long, int> a, pair<long long, int > b) {
            return double(a.first)/ double(a.second)  > double(b.first) / double(b.second);
        });
    }
    return 0;
}
