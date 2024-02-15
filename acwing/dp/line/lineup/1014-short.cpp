#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;


const int N = 5100;

typedef pair<int,int> PII;
PII a[N];
int f[N];
int main() {
    
    int n;
    cin >> n;
    
    for (int i = 0; i < n; i ++) {
        cin >> a[i].first >> a[i].second;
    }
    
    
    sort(a, a + n);
    int res = 0;
    for (int i = 0; i < n; i ++) {
        f[i] = 1;
        for (int j = 0; j < i; j ++) {
            
            if (a[i].second > a[j].second) {
                f[i] = max(f[i], f[j] + 1);
            }
        }
        res = max(res, f[i]);
    }
    cout << res << endl;
    
    
    return 0;
}