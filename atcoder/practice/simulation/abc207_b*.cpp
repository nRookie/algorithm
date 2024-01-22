#include<iostream>

using namespace std;

int main() {


    int A,B,C,D;
    cin >> A >> B >> C >> D;

    // A + BX
    // Cx
    
    // A + Bx <= Cx * D
    // A <= (C *D - B) x
    // 1 <= (C * D - B) / A 
    int step = 0;
    int cyan = A, red = 0;

    for (int i = 1; i < A; i ++ ) {
        cyan += B;
        red += C;
        if (cyan <= red * D) {
            cout << i << endl;
            return 0;
        }
    }

    cout << -1 << endl;
    return 0;
}