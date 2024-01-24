#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;


int main() {
    int r1, c1, r2, c2;

    cin >> r1 >> c1 >> r2 >> c2;


    if (r1 == r2 && c1 == c2) {
        cout << 0 << endl;
        return 0;
    }

    if (c1 + r1 == c2 + r2 || r1 - c1 == r2 - c2 || abs(r1 - r2) + abs(c1 - c2) <= 3) {
        cout << 1 << endl;
        return 0;
    }


    if ( abs((r1 + c1)  - (r2 + c2 ) ) <= 3 ) {
        cout << 2 << endl;
        return 0;    
    }

    if ( abs( (r1 - c1) - (r2 - c2) ) <= 3) {
        cout << 2 << endl;
        return 0;
    }

    if ( abs(r1 - r2) + abs(c1 - c2) <= 6) {
        cout << 2 << endl;
        return 0;
    }


    // if ((r1 + c1) % 2 == (r2 + c2) % 2) {
    //     cout << 2 << endl;
    //     return 0;
    // }
    if ((r1 + c1 + r2 + c2) % 2 == 0) {
        cout << 2 << endl;
        return 0;
    } 

    cout << 3 << endl;
    return 0;

}