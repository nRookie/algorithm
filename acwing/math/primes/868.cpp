#include<iostream>
using namespace std;



const int N = 1e7;


int primes[N];

int cnt = 0;

bool st[N];

int getPrimes(int x) {
    for (int i = 2; i <= x; i ++) {
        if (!st[i]) primes[cnt ++] = i;

            for (int j = 0; primes[j] <= x / i; j ++) {
                st[i * primes[j]] = true;
                if ((i % primes[j]) == 0) break;
            }
    }
}


int main() {
    int n;
    cin >> n;
    getPrimes(n);
    cout << cnt << endl;
}