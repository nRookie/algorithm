#include<iostream>

using namespace std;


char a[60];

int main() {
    int n, k;

    cin >> n >> k;

    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        if (i == k) {
            a[i] += 32;
        }
    }


    for (int i = 1; i <= n; i ++) cout<<a[i];
    cout << endl;
    
}