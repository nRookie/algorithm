#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int N = 100010,  MOD = 1e9 + 7;

typedef long long ll;

string s;
int n;
ll f[N][2];
int main () {
	cin >> s;
	n = s.size ();
	f[0][0] = 1,f[0][1] = 0;
    // f[i][0] : is the number of pairs {a, b} of lengthi that have sum a + b = L;
    // f[i][1] : is the number of pairs {a, b} of lengthi that have sum a + b < L;
	for (int i = 1;i <= n;i++) {
		if (s[i - 1] == '1') {
			f[i][0] = f[i - 1][0] * 2 % MOD; // since f[i - 1][0] equals to the previous i - 1 digit  of the  L. we can either 
            // add 1 to a, 0 to b, or 0 to a, 1 to b. thus we can have f[i - 1][0] * 2 method to make the a + b = L of length i.
			f[i][1] = (f[i - 1][1] * 3 + f[i - 1][0]) % MOD;
            // since f[i - 1][1] is the number of pairs {a, b} of lengthi that have sum a + b < L;
            //  
            // there are three way, because f[i - 1][1] make sure the previous i - 1 digit a + b is smaller than L. thus 
            // we can try to add 0 to a, 0 to b.   1 to a, 0 to b,  0 to a , 1 to b. and the f[i - 1][1] * 3 is still smaller than  L.
            // and for f[i - 1][0], if we add 0 to the ith digit. we have one solution, which also makes it  smaller than L.
            // that is why  f[i][1] = (f[i - 1][1] * 3 + f[i - 1][0]) % MOD;
		}
		else {
			f[i][0] = f[i - 1][0]; // we can only add 0
			f[i][1] = f[i - 1][1] * 3 % MOD; // we 
		}
	}

    // because we are counting the number of a + b <= L, that is why f[n][0] + f[n][1] is used here.
	cout << (f[n][0] + f[n][1]) % MOD << endl;
	return 0;
}