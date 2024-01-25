#include<iostream>

using namespace std;

int main() {
    // 1 ~ N box
    // 1  red ball,   others 1 white ball.
    // following M operations one by one .

    // ith operation, pick one ball from box xi,    put it into yi.

    // find the number of boxes may contain red ball

    int n, m;

    cin >> n >> m;

    int box[100100] = {0};
    int red[100100] = {0};
    for (int i = 1; i <= n; i ++) {
        box[i] = 1;
    }
    red[1] = 1;
    while (m --) {
        int a , b;
        cin >> a >> b;
        box[a] -= 1;
        box[b] += 1;

        if (red[a] == 1) {
            red[b] = 1;
            if (box[a] == 0) {
                red[a] = 0;
            }
        }

    }
    // cout << endl;
    int count = 0;
    for (int i = 1; i <= n; i ++) {
        // cout << red[i] << " ";
        if (red[i] > 0)  {
            count ++;
        }
    }
    // cout << endl;
    cout << count << endl;
// 3 2
// 1 2
// 2 3

//   2
// 3 3
// 1 2
// 2 3
// 2 3
//
// r w w 
//   w + r w
//   w    w + r
//        w + w + r
    return 0;
}