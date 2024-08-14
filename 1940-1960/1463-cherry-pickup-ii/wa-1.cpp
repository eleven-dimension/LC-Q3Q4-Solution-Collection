#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        const int dx[] = {-1, 0, 1};
        int n = grid.size(), m = grid[0].size();
        
        vector<vector<int>> f(m, vector<int>(m));

        f[0][m - 1] = grid[0][0] + grid[0][m - 1];
        for (int r = 1; r < n; r++) {
            vector<vector<int>> g(m, vector<int>(m));
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < m; j++) {
                    for (int d1 = 0; d1 < 3; d1++) {
                        for (int d2 = 0; d2 < 3; d2++) {
                            int pre_i = i - dx[d1], pre_j = j - dx[d2];
                            if (pre_i < 0 || pre_j < 0 || pre_i >= m || pre_j >= m) {
                                continue;
                            }
                            g[i][j] = max(g[i][j], f[pre_i][pre_j] + (i == j ? grid[r][i] : grid[r][i] + grid[r][j]));
                        }
                    }
                }
            }
            f = g;
        }

        int ans = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                ans = max(ans, f[i][j]);
            }
        }
        return ans;
    }
};