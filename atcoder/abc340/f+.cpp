#include<iostream>
#include<cstring>
using namespace std;


// GCD(X,Y)
// 

typedef long long ll;
ll exgcd(ll a, ll b, ll & x, ll&  y) {
    
        if (b == 0) {
            x = 1ll;
            y = 0;
            return a;
        }
        ll d = exgcd(b, a % b, y , x);
        y -= a/b * x;  
        
        return d;
}


int main () {
    ll a, b, y, x;
	cin >> a >> b;
	ll d = exgcd (a,b,y,x);
	x = -x;
	if (2 % d) {
		puts ("-1");
		return 0;
	}
	x = x * (2 / d),y = y * (2 / d);
    cout << x << " " << y << endl;
	cout << x << ' ' << y << endl;
	return 0;
}