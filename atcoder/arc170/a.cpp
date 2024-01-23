#include <iostream>
#include <string>

using namespace std;

int minOperationsToEqual(const string& S, const string& T) {
    string U;
    for (int i = 0; i < S.size(); ++i) {
        if (S[i] != T[i]) {
            U += (T[i] == 'A') ? '(' : ')';
        }
    }

    int balance = 0, insertLeft = 0;
    for (char ch : U) {
        if (ch == '(') {
            balance++;
        } else {
            balance--;
            if (balance < 0) {
                insertLeft++;  // Need one more '(' at the start
                balance = 0;
            }
        }
    }

    // If balance > 0, need that many ')' at the end
    int insertRight = (balance > 0) ? balance : 0;

    // Check if it's impossible to make U a valid sequence
    if ((insertLeft > 0 && T.front() != 'A') || (insertRight > 0 && T.back() != 'B')) {
        return -1;
    }

    return (U.size() / 2) + insertLeft + insertRight;
}

int main() {
    int N;
    string S, T;

    cin >> N >> S >> T;

    cout << minOperationsToEqual(S, T) << endl;

    return 0;
}
