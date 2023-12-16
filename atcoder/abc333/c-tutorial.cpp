
#include<iostream>

using namespace std;


typedef long long ll;

ll r[13];
int main() {
    r[0] = 1;
    int n ;
    cin >> n;
    for (int i = 1; i <= 12; i ++) {
        r[i] = r[i - 1] * 10 + 1;
    }

    for (int i = 0; i < 12; i ++) {
        for (int j = 0; j <= i; j ++) {
            for (int k = 0; k <= j; k ++ ) {
                n -= 1;
                if (n == 0)  {
                    cout <<(r[i] + r[j] + r[k]);
                    break;
                }
            }
        }
    }
    return 0;
}