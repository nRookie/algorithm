#include <iostream>
#include <string>
#include <cctype>   
using namespace std;
bool isValidString(const string& S) {
    if (!std::isupper(S[0])) {
        return false;
    }
    for (int i = 1; i < S.length(); i++) {
        if (!std::islower(S[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    string S;
    cin >> S;

    if (isValidString(S)) {
        cout <<"Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}
