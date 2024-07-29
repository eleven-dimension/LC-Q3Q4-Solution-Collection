#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    using ll = long long;
    vector<long long> minOperations(vector<int>& nums, vector<int>& queries) {
        ll n = nums.size(), m = queries.size();
        sort(nums.begin(), nums.end());

        vector<ll> up(n), down(n), ans(m);
        ll tmp_sum = 0;
        for (ll i = 0; i < n; i++) {
            tmp_sum += nums[i];
            up[i] = (i + 1) * nums[i] - tmp_sum;
        }

        tmp_sum = 0;
        for (ll i = n - 1; i >= 0; i--) {
            tmp_sum += nums[i];
            down[i] = tmp_sum - (n - i) * nums[i];
        }

        for (ll i = 0; i < m; i++) {
            auto it = upper_bound(nums.begin(), nums.end(), queries[i]);
            if (it == nums.end()) {
                ans[i] = up[n - 1] + n * (queries[i] - nums[n - 1]);
            } else if (it == nums.begin()) {
                ans[i] = down[0] + n * (nums[0] - queries[i]);
            } else {
                ll cur_id = distance(nums.begin(), it);
                ans[i] = (
                    up[cur_id - 1] + cur_id * (queries[i] - nums[cur_id - 1]) + 
                    down[cur_id] + (n - 1 - cur_id + 1) * (nums[cur_id] - queries[i])
                );
            }
        }
        return ans;
    }
};

int main() {
    {
        vector<int> nums = {3,1,6,8};
        vector<int> queries = {1,5};
        Solution sol;

        auto ans = sol.minOperations(nums, queries);
        for (auto& x : ans) {
            cout << x << " ";
        }
    }
}