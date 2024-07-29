#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        sort(tasks.begin(), tasks.end(), 
            [](const vector<int>& a, const vector<int>& b) {
                return a[1] - a[0] == b[1] - b[0] ? a[1] > b[1] : a[1] - a[0] > b[1] - b[0];
            }
        );
        int n = tasks.size();
        int ans = tasks[n - 1][1];
        for (int i = n - 2; i >= 0; i--) {
            if (ans + tasks[i][0] >= tasks[i][1]) {
                ans += tasks[i][0];
            } else {
                ans = tasks[i][1];
            }
        }
        return ans;
    }
};

int main() {
    {
        vector<vector<int>> tasks = {{1,2},{2,4},{4,8}};
        Solution sol;
        cout << sol.minimumEffort(tasks) << endl;
    }
}