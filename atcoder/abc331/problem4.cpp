#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


int a[100100];
int sum[100100];
int N;

int preSum[100100];
int main() {
    
    scanf("%d", &N);
    int maxN = 0;
    for (int i = 0; i < N; i ++) {
        scanf("%d", &a[i]);
        sum[a[i]] += a[i];
        maxN = max(a[i], maxN);
    }

    // for (int i = 1; i <= maxN + 1; i ++) {
    //     cout << sum[i] << " ";
    // }
    // cout << endl;

    for (int i = 1; i <= maxN + 1; i ++) {
        preSum[i] = preSum[i - 1] + sum[i - 1];
    }
    // cout << endl;

    // for (int i = 1; i <= maxN + 1; i ++) {
    //     cout << i << " : " <<  preSum[i] << " ";
    // }
    // cout << endl;

    for (int i = 0; i < N; i ++) {
        // cout << a[i] << ":" << (preSum[N] - preSum[a[i] + 1] ) << " ";
        cout << (preSum[maxN + 1] - preSum[a[i] + 1] ) << " ";
    }

    return 0;

}