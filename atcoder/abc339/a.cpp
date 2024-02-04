#include <iostream>
#include <string>
using namespace std;

int main() {
    string S;
    cin >> S;

    size_t pos = S.rfind('.');
    string lastSubstring = S.substr(pos + 1);
    cout << lastSubstring << endl;

    return 0;
}
