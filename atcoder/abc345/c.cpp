#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main() {

    string s;
    cin >> s;
    long long n = s.length();
    map<char, long long> freq;
    for (char c : s) {
        freq[c]++;
    }
    // abc
    // bac
    // cba
    // acb

    // 3 * (2) / 2
    // aabc
    // baac
    // abac
    // aaaab
    // aaab
    // baaa
    // abaa
    // aaba

    // aabb

    // aabb
    // baab
    // abab
    // baba
    // abba

    // 2 
    bool identical  = false;
    long long totalSwaps = n * (n - 1) / 2;
    for (auto& p : freq) {
        if (p.second > 1) {
            identical = true;
            totalSwaps -= p.second * (p.second - 1) / 2;
        }
    }
    
    cout << totalSwaps + identical << endl;
}
