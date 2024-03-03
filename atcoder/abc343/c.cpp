#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;



const int N = 1e6 + 10, M = 4 * N;

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


// K 
// there is a positive integer x such that x^3 = K

// the decimal representation of K without leading zeros is a palindrome. More precisely, if K is represented as K = i = 0... L - 1 Ai10i
//0, 9
// 1... 9
// 0,1, ..., L - 1

// 

void output(ll x) {
    vector<int> num;
    // cout << x << endl;
    while (x ) {
        num.emplace_back(x % 10);
        x/= 10;
    }
    reverse(num.begin(), num.end());
    int n = num.size();
    // 0, 1, 2 3
    // 

    // 0, 1,2,3,4
    // 
    for (int i = 0; i < (n + 1)/ 2; i ++) {
        cout << num[i];
    }

    for (int i = n / 2 - 1; i >= 0; i --) {
        cout << num[i];
    }
    cout << endl;
}

bool check1(ll x) {
    vector<int> num;
    ll sum = x* x* x;
    // cout << x << endl;
    while (sum) {
        num.emplace_back(sum % 10);
        sum/= 10;
    }
    int n = num.size();

    ll l = 0, r = n - 1;
    while (l < r) {
        if (num[l] != num[r]) {
            return false;
        } 
        l ++, r -- ;
    }
    return true;
}
bool check(ll x, ll n) {
    if (x * x * x <= n) { 
        return true;
    } else {
        return false;
    }
}

int main() {
    ll n;
    cin >> n;
    // cout << r << endl;
    ll L = 1, R = cbrt(n) + 1;
    while (true) {
        ll l = 1, r = R ;
        while (l < r) {
            ll mid = l + r + 1>> 1;
            // cout << l <<  " " << r << " " << mid << endl;
            if (check(mid, n)) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }   
        if(check1(r)) {
            output(r * r * r);
            return 0;
        } else {
            R = r - 1;
        }
    }
    return 0;
}