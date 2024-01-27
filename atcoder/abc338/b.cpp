#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int main() {

    string s;
    cin >> s;

    int n = s.size();
    int count[26] = {0};

    for (int i = 0; i < n; i ++) {
        count[s[i] - 'a']++;
    }

    int maxx = 0;

    for (int i = 1; i < 26; i ++) {
        if (count[maxx] < count[i]) {
            maxx = i;
        }
    }

    cout << char(maxx + 'a') << endl;
}