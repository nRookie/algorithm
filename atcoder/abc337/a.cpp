#include<iostream>
#include<cstring>
using namespace std;



int a[1000];
int b[1000];
int main() {

    int n;
    cin >> n;

    int sum1 = 0, sum2 = 0;

    for (int i = 1; i <= n; i ++) {
        cin >> a[i] >> b[i];
        sum1 += a[i];
        sum2 += b[i];
    }

    if (sum1 > sum2) cout << "Takahashi" << endl; 
    else if (sum1 < sum2) cout << "Aoki" << endl; 
    else cout << "Draw" << endl;
    return 0;
}