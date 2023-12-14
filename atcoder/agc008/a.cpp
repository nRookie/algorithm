// #include<iostream>
// #include<cmath>
// using namespace std;


#include<iostream>
#include<cmath>
using namespace std;

int main() {
    long long x, y;
    cin >> x >> y;

    long long res = 0;
    if (x < 0 && y < 0) {
        if (x < y) {
            res = y - x;
        } else {
            res = 2 + x - y;
        }
    } else if (x > 0 && y > 0) {
        if (x > y) {
            res = 2 + x - y;
        } else {
            res = y - x;
        }
    } else if (x > 0 && y < 0 || x < 0 && y > 0) {
        res = abs(x + y) + 1;
    } else if (x == 0 && y == 0) {
        res = abs(x - y);
    } else if (x == 0 && y > 0) {
        res = y;
    } else if ( x == 0 && y < 0) {
        res = -y + 1;
    } else if ( x > 0 && y == 0) {
        res = x + 1;
    } else if (x < 0 && y == 0) {
        res = -x;
    } 
    cout << res << endl;
    return 0;
}



// typedef long long ll;
// int main(){
// 	ll x,y;
// 	scanf("%lld%lld",&x,&y);
// 	ll xx=abs(x),yy=abs(y);
// 	ll ans=yy+xx+(x>0)+(y<0);
// 	if(xx>=yy)ans=min(ans,xx-yy+(x>0)+(y>0));
// 	if(xx<=yy)ans=min(ans,yy-xx+(x<0)+(y<0));
// 	printf("%lld\n",ans);
// 	return 0;
// }