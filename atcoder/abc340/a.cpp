#include <iostream>

using namespace std;


int main() {
    int A, B, D;
    
    cin >> A >> B >> D;
    
    for (int term = A; term <= B; term += D) {
        cout << term << " ";
    }
    cout << endl;
    
    return 0;
}