#include<iostream>
#include<unordered_map>
using namespace std;

int main() {

    // 1 2 3  4
    //

    unordered_map<int, int> count;

    int n;
    long long sum = 0;
    cin >> n;
    for (int i = 0; i < n; i ++) {
        int a; 
        cin >> a;
        count[a] ++;
        sum += a;
    }

    int q;
    cin >> q;

    while(q --) {
        int b, c;
        cin >> b >> c;
        if (count[b] > 0) {
            sum += (c - b) * count[b];
            count[c] += count[b];
            count[b] = 0; 
        } 
        
        cout << sum << endl;
    }
    return 0;
}