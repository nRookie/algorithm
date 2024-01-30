#include<iostream>
#include<vector>
using namespace std;

int main() {

    int T;

    cin >> T;

    while(T --) {
        int n ;
        cin >> n;
        int res = 0;
        while (n --) {
            int a ;
            cin >> a;
            if (a & 1) {
                res ++;
            }

        }
        cout <<res << endl;
    }

    return 0;
}