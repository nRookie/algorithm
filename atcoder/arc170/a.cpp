#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int minOperationsToEqual(string S, string T) {
    string U;
    int N = S.size();

    // Create string U based on differences between S and T
    for (int i = 0; i < N; ++i) {
        if (S[i] != T[i]) {
            U += (T[i] == 'A') ? '(' : ')';
        }
    }

    // Check if U is a valid parentheses sequence
    int balance = 0, insertions = 0;
    for (char ch : U) {
        if (ch == '(') {
            balance++;
        } else {
            balance--;
            if (balance < 0) {
                balance = 0;
                insertions++;
            }
        }
    }

    // If balance is non-zero, it's impossible to make S equal T
    if (balance != 0) return -1;

    // Answer is half the length of U plus the number of insertions
    return U.size() / 2 + insertions;
}

int main() {
    int N;
    string S, T;

    cin >> N >> S >> T;

    int result = minOperationsToEqual(S, T);
    cout << result << endl;

    return 0;
}
