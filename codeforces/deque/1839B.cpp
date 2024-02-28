#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<set>
#include<unordered_map>
#include<stack>
#include<queue>
using namespace std;



const int N = 2* 1e6 + 10, M = 4 * N;

typedef pair<int,int> PII;
int h[N], ne[M], e[M], w[M], idx;

void add (int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}


typedef long long ll;
ll exgcd(ll a, ll b, ll & x, ll&  y) {
    
        if (b == 0) {
            x = 1;
            return a;
        }
        ll d = exgcd(b, a % b, y , x);
        y -= a/b * x;  
        
        return d;
}



// a, 
// n lamps,  1 to n
// two integer params, ai and bi

// three state,  turned on, turned off , broken.

// Initially all lamps are turned off. 
// In one operation you can select one lamp that is turned off and turn it on
// bi point for turning lamp i on


// turned on as x,
// ai <= x simultaneously break
// 
void solve() {
    int n;
    cin >> n;
    vector<PII> a(n);
    for (int i = 0; i < n; i ++) {
        int x, y;
        cin >> x >> y;
        a[i] = {x, y};
    }

    sort(a.begin(), a.end(), [](PII a, PII b){
        if (a.first < b.first) {
            return true;
        } else if (a.first > b.first) {
            return false;
        } else {
            return a.second > b.second;
        }
    });
    int x = 0;
    ll sum = 0;
    int lighting = 0;
    deque<int> last;
    unordered_map<int, int> cnt;
    for (int i = 0; i < n; i ++) {
        // cout << a[i].first << " " << a[i].second << " " << x <<  " " <<  lighting << endl;

        while (last.size() && last.front() <= x) {
            lighting -= cnt[last.front()];
            cnt[last.front()] = 0;
            last.pop_front();
        }
        if (a[i].first > x) {
            sum += a[i].second;
            lighting ++;
            if (last.size() == 0 || last.back() != a[i].first) {
                // cout << "pushing" << endl;
                last.push_back(a[i].first);
            }
            cnt[a[i].first] ++;
            x = max(lighting, x);
        }
        // cout << a[i].first << " " << a[i].second << " " << x <<  " " <<  lighting << endl;
    }
    cout << sum << endl;
 
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}