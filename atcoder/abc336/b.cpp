#include<iostream>

using namespace std;



int countTrailingZeros(int N) {

    int ctz = 0;
    while ((N & 1) == 0) {
        N >>= 1;
        ctz++;
    }
    return ctz;
}
int main() {
    int n;
    cin >> n;

    cout << countTrailingZeros(n) << endl;
}