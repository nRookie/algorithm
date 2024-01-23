#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
  string s;
  int k;
  cin >> s >> k;
  sort(s.begin(),s.end());
  while(k>1){
    next_permutation(s.begin(),s.end());
    k--;
  }
  cout << s << '\n';
  return 0;
}


void nextPermutation(vector<int>& nums) {
       int i = nums.size() - 2;
       while (i >= 0 && nums[i] >= nums[i + 1]) {
           i --;
       }

       if (i >= 0) {
           int j = nums.size() - 1;
           while(j >= 0 && nums[i] >= nums[j]) {
               j --;
           }
           swap(nums[i], nums[j]);
       }
       reverse(nums.begin() + i + 1, nums.end());
    }