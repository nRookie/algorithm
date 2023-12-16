

#include<iostream>
#include<unordered_map>
using namespace std;

unordered_map<string, int> m ;
int main() {

    char s1, s2;
    char t1, t2;
    string res1="", res2 = "";
    cin >> s1 >> s2 >> t1 >> t2;

    res1 += s1;
    res1 += s2;
    res2 += t1;
    res2 += t2;
    for (int i = 0; i < 5; i ++) {
        string s1 = "", s2 = "";
        int i1 = i + 1;
        if (i1 >= 5) i1 -= 5;
        int i2 = i - 1;
        if (i2 < 0) i2 += 5;
    
        s1 += i +'A';
        s1 += i1 + 'A';   
        s2 += i + 'A';
        s2 += i2 +  'A';

        int i3 = i + 2;
        if (i3 >= 5) { i3 -= 5;}
        int i4 = i - 2;
        if (i4 < 0) { i4 += 5;}

        string s3= "", s4= "";

        s3 += i +'A';
        s3 += i3 +'A';
        s4 += i + 'A';
        s4 += i4 +'A';

        m[s1] = 1;
        m[s2] = 1;

        m[s3] = 2;
        m[s4] = 2;
    }

    if (m[res1] == m[res2]) {
        cout <<"Yes" << endl;
    } else {
        cout << "No" << endl;
    }



    return 0;
}