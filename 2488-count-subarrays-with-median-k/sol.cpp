#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countSubarrays(vector<int>& nums, int k) {
        int index = find(nums.begin(), nums.end(), k) - nums.begin();
        unordered_map<int, int> even, odd;

        int n = nums.size();
        int cursor = 0;
        for (int i = index; i < n; i++) {
            if (nums[i] > k) {
                cursor++;
            } else if (nums[i] < k) {
                cursor--;
            }
            if ((i - index) % 2 == 1) {
                odd[cursor]++;
            } else {
                even[cursor]++;
            }
        }

        cursor = 0;
        int ans = 0;
        for (int i = index; i >= 0; i--) {
            if (nums[i] > k) {
                cursor++;
            } else if (nums[i] < k) {
                cursor--;
            }

            if ((index - i) % 2 == 1) {
                ans += odd[-cursor] + even[1 - cursor];
            } else {
                ans += even[-cursor] + odd[1 - cursor];
            }
        }
        return ans;
    }
};

int main() {
    vector<int> nums = {3,2,1,4,5};
    int k = 4;
    Solution sol;
    cout << sol.countSubarrays(nums, k);
}