#include<iostream>

using namespace std;


const int N = 1e3 + 7;
int n;
int primes[N];

bool isPrime(int x) {
    if (x == 1) return false;
    for (int i = 2; i <= x/ i; i ++) {
        if (x % i == 0) return false;
    }

    return true;
}



int main() {
    cin >> n;

    while (n -- ) {
        int a ;
        cin >> a ;

        if (isPrime(a)) cout << "Yes" << endl;
        else cout << "No" << endl;
    }

    return 0;
}