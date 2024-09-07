#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        const int N = 105;
        bool f[N][N][2 * N] = {false};
        f[0][0][0] = f[0][1][0] = f[1][0][0] = true;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                for (int k = 0; k < 2 * N; k++) {
                    if (grid[i - 1][j - 1] == '(' && k - 1 >= 0) {
                        f[i][j][k] |= f[i - 1][j][k - 1];
                        f[i][j][k] |= f[i][j - 1][k - 1];
                    }
                    if (grid[i - 1][j - 1] == ')' && k + 1 < 2 * N) {
                        f[i][j][k] |= f[i - 1][j][k + 1];
                        f[i][j][k] |= f[i][j - 1][k + 1];
                    }
                }
            }
        }
        return f[n][m][0];
    }
};