#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

using namespace std;

class Solution {
public:
  int smallestRangeII(vector<int> &nums, int k) {
    int ans = *ranges::max_element(nums) - *ranges::min_element(nums);
    ranges::sort(nums);
    int n = nums.size();
    for (int lim = 0; lim <= n - 2; lim++) {
      vector<int> candidates = {nums[0] + k, nums[lim] + k, nums[lim + 1] - k,
                                nums[n - 1] - k};
      ans = min(ans, *ranges::max_element(candidates) -
                         *ranges::min_element(candidates));
    }
    return ans;
  }
};