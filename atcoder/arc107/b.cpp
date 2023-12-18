#include<iostream>
#include<algorithm>
using namespace std;


int f(int N, int K) {
    return min(K - 1, 2* N + 1 - K);
}
int main() {
    // f(n,k) = min(k - 1, 2n + 1 - k)


    // a + b - (c + d ) =  K

    // a + b = (c + d) + K
    // a + b - K = c + d
    // let a + b = x
    // then c + d = x - k


    // for a + b - k = x
    // f(N, x) = min(x - 1, 2N + 1 - x)

    // for c + d + k= x = a + b
    // c + d = x - k
    // f(N, x -k) = min(x - k - 1, 2N + 1 - (x - k))

    // int N, K;

    // cin >> N >> K;
    // int res = 0;
    // for (int x = 2; x <= 2 * N; x++) {
    //     if (x - K >= 2 && x - K <= 2 * N) {
    //     res += f(N, x) * f(N, x - K);
    //     }
    //     // cout << res << endl;
    // }

    // cout << res << endl;

    int N, K;
    cin >> N >> K;

    long long totalQuadruples = 0;

    // Calculate the total number of quadruples
    for (int x = 2; x <= 2 * N; ++x) {
        if (x - K >= 2 && x - K <= 2 * N) {
            totalQuadruples += (long long) f(N, x) * f(N, x - K);
        }
    }

    cout << totalQuadruples << endl;


    return 0;
}