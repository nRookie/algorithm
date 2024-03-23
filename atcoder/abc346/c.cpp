#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;


int main() {
  long long n, k;
  cin >> n >> k;

    set<int> elements;

  for (int  i = 0; i < n; i ++) {
    int a;
    cin >> a;
    if (a <= k) 
    elements.insert(a);
  }
    long long totalSum = k * (k + 1) / 2;

    for (int a : elements) {
        totalSum -= a;
    }

    cout << totalSum << endl;
}