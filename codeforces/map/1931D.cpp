#include<iostream>
#include<map>
using namespace std;

typedef pair<int,int> PII;
void solve() {
    int n, x, y;

    map<PII, int> cnt;
    cin >> n >> x >> y;
    long long ans = 0;
    for (int i = 0; i < n; i ++) {
        int a;
        cin >> a ;
        int xmod = a % x;
        int ymod = a % y;
        PII key = {(x - xmod) % x, ymod};

        if (cnt.find(key) != cnt.end())  {
            ans += cnt[key];
        }
        cnt[{xmod, ymod}] ++;
    }

    cout << ans << endl;


}
int main() {


    int t;
    cin >> t;
    while (t --) {
        solve();
    }
}