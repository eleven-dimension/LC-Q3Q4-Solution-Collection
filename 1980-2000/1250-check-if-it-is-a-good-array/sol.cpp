#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isGoodArray(vector<int>& nums) {
        int res = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            res = gcd(res, nums[i]);
        }
        return res == 1;
    }
};

int main() {
    {
        vector<int> v = {12,5,7,23};
        Solution sol;
        cout << boolalpha << sol.isGoodArray(v) << endl;
    }
    {
        vector<int> v = {3, 6};
        Solution sol;
        cout << boolalpha << sol.isGoodArray(v) << endl;
    }
}