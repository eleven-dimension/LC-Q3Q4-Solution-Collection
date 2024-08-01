#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int n = hours.size();
        vector<int> sum(n);
        sum[0] = hours[0] > 8 ? 1 : -1;
        for (int i = 1; i < n; i++) {
            sum[i] = sum[i - 1] + (hours[i] > 8 ? 1 : -1);
        }

        vector<int> suffix_max(n);
        suffix_max[n - 1] = sum[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            suffix_max[i] = max(suffix_max[i + 1], sum[i]);
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (sum[i] > 0) {
                ans = max(ans, i + 1);
            }
            auto it = lower_bound(suffix_max.begin() + i, suffix_max.end(), sum[i], std::greater<int>());
            int index = it - suffix_max.begin() - 1;
            if (index < i) continue;
            ans = max(ans, index - i);
        }
        return ans;
    }
};

int main() {
    vector<int> hours = {9,9,6,0,6,6,9};
    Solution sol;
    cout << sol.longestWPI(hours);
}