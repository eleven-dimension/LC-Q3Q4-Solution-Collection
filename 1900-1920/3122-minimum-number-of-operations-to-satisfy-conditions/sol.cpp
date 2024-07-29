#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumOperations(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> cnt(m, vector<int>(10));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cnt[i][grid[j][i]]++;
            }
        }

        vector<vector<int>> f(m, vector<int>(10, INT_MAX));
        for (int i = 0; i < 10; i++) {
            f[0][i] = n - cnt[0][i];
        }

        for (int i = 1; i < m; i++) {
            for (int j = 0; j < 10; j++) {
                for (int k = 0; k < 10; k++) {
                    if (k != j) {
                        f[i][j] = min(f[i][j], f[i - 1][k] + n - cnt[i][j]);
                    }
                }
            }
        }

        int ans = INT_MAX;
        for (int i = 0; i < 10; i++) {
            ans = min(ans, f[m - 1][i]);
        }
        return ans;
    }
};

int main() {
    vector<vector<int>> v = {{1,0,2},{1,0,2}};
    Solution sol;
    cout << sol.minimumOperations(v);
}