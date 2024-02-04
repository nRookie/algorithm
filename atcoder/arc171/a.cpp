#include <iostream>
#include<cmath>
#include<algorithm>
using namespace std;
bool canPlace(int N, int A, int B) {
    int c = min(N - A, (N + 1) / 2);
    return   (N - A) * c >= B;
}
// 6 4


int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, A, B;
        cin >> N >> A >> B;
        
        cout << (canPlace(N, A, B) ? "Yes" : "No") << endl;
    }
    return 0;
}


// https://atcoder.jp/contests/arc171/editorial/9226
