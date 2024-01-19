#include<iostream>

using namespace std;


const int N = 1000010;

int a[N];
int pre[N];

int n, m, l , r ;


int main() {

    cin  >> n >> m;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];

        pre[i] = pre[i - 1] + a[i];
    }


    while (m --) {
        int l, r ;
        cin >> l >> r ;

        cout << pre[r] - pre[l - 1] << endl;
    }
    return 0;


}