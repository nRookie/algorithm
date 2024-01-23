#include<iostream>
using namespace std;

int dfs(int a, int b , int c) {
    if (a & 1 || b & 1 || c & 1) return 0;
    return dfs(b / 2 + c / 2, a / 2 + c / 2, b / 2 + a / 2) + 1 ;
}

int main() {
    int a , b , c ;
    cin >> a >> b >> c;

    if (a == b && b == c && (a & 1 == 0) ) {
        cout << -1 << endl;
        return 0;
    }
    cout <<  dfs(a, b, c)  << endl;

    return 0;
}