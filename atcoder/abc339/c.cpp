#include<iostream>

using namespace std;

const int N = 2 * 1e5 + 10;
int a[N];
int main() {

    int n; 
    cin >> n;
 
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
    }

    long long currentNum = 0;
    for (int i = 0; i < n; i ++) {
            currentNum += a[i];
            if (currentNum < 0) {
                currentNum = 0;
            }
    }

    cout << currentNum << endl;
    return 0;
}