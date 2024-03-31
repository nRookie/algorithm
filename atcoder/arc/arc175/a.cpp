#include <iostream>
#include <vector>
using namespace std;

const int MOD = 998244353;

int main() {
    int N;
    cin >> N;
    vector<int> Ps(N);
    for (int i = 0; i < N; ++i) {
        cin >> Ps[i];
        Ps[i] -= 1; // Adjust for 0-based indexing
    }
    string S;
    cin >> S;

    long long answer_left = 1, answer_right = 1;
    vector<bool> took_spoon(N, false); // indicate the spoon i has been taken

    // The strategy invovles simulation. Assume that everyone who made the 1-st, ..., (i - 1)-ith actions has taken the spoon on their
    // left side.
    // In the i-th action, consider whether there are spoons remaining on each side of person Pi.

    // The spoon on the left side of person Pi is always there, and the spoon on the right side is there if and only if person(Pi + 1) has not acted yet.
    // Here, person (N + 1) refers to person 1.

    // Now that we know which spoons remain when person Pi acts, we consider the dominant hand of person Pi that allows them to take the sppon on their 
    // left side and count towards the answer, specifically, we initialize the answer to 1 and perform the following process 
    // for i = 1, ..., N in order while simulating the actions


    // if the spoon on the right side of person Pi is remaining :
    // Person Pi must be left-handed, if the corresponding character in string S is 'R', multiply the answer by 0; otherwise do nothing.
    // if the spoon on the right side of person Pi is not remaining
    // Person Pi may be left- or right-handed. If the corresponding character in string S is ?, multiply the answer by 2; otherwise do nothing.

    // By performing the above process 

    for (auto P : Ps) { // assume taking the spoon at the left side
        if (took_spoon[(P + 1) % N]) {  // the Spoon on the right side is not remaining,
            if (S[P] == '?') answer_left = (answer_left * 2) %MOD; // then user can only take the spoon on his left, so it does not matter whether he is left handed or right handed.
        } else { // the spoon on the right side is remaining
            if (S[P] == 'R') { // Person P must be left handed, be cause if the Person P is right handed he should take the spoon.
                answer_left = 0;
            }
        }
        took_spoon[P] = true;
    }

    fill(took_spoon.begin(), took_spoon.end(), false);
    for (auto P : Ps) { // assume taking the spoon at the right side

        if (took_spoon[ P % N]) {   // the Spoon on the left side is not remaining,
            if (S[P] == '?') answer_right = (answer_right * 2) %MOD;  
        } else { // the Spoon on the left side is remaining
            if (S[P] == 'L') { 
                answer_right = 0;
            }
        }
        took_spoon[(P + 1) % N] = true;
    }
    std::cout << (answer_left + answer_right ) % MOD << endl;
    return 0;
}
