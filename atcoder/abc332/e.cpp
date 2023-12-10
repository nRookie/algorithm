#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

int n, m;
string s;


int main() {
    cin >> n >> m;

    vector<int> p(n);
    vector<int> bag(m);
    long long sum = 0;
    for (int i = 0; i < n; i ++) {
        cin >> p[i];
        sum += p[i];
    }

    long long avg = sum / m;
    sort(p.begin(), p.end());


    for (int i = 0, j = 0; i < n && j < m; i ++) {
        if(bag[j] < avg) {
            bag[j] += p[i]
        } else {
            
        }
    }

    
    return 0;
}