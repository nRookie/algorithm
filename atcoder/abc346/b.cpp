#include <iostream>

using namespace std;

int main() {
    int W, B;
    cin >> W >> B;
    string s = "wbwbwwbwbwbw";
    for (int i = 0; i < 4; i ++) {
        s += s;
    }
    
    int n = s.size();
    for (int i = 0; i < n; i ++) {
        int w = 0, b = 0;
        for (int j = i; j < n; j ++) {
            if (s[j] == 'w') w++;
            if (s[j] == 'b') b++;

            if (W == w && b == B) {
                cout << "Yes" << endl;
                return 0;
            }
        }
    }

    cout << "No" << endl;

    return 0;
}
