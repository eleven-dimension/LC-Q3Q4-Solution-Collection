#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int containVirus(vector<vector<int>>& isInfected) {
        const int N = 55;
        int n = isInfected.size(), m = isInfected[0].size();
        bool blocked[N][N][4] = {false};
        auto in = [&](int x, int y) {
            return 0 <= x && x < n && 0 <= y && y < m;
        };
        const int dx[] = {0, 0, -1, 1};
        const int dy[] = {1, -1, 0, 0};

        auto game_over = [&]() {
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (isInfected[i][j] == 1 || isInfected[i][j] == -1) {
                        cnt++;
                    }
                }
            }
            return cnt == m * n;
        };

        int wall_used = 0;
        while (true) {
            int mx = -1, my = -1, max_impact = 0;
            int visited[N][N] = {0};
            bool success = true;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (isInfected[i][j] == 1 && visited[i][j] == 0) {
                        success = false;
                        unordered_set<int> new_grids;
                        queue<pair<int, int>> q;
                        q.emplace(i, j);
                        visited[i][j] = 1;
                        while (q.size()) {
                            auto [x, y] = q.front();
                            q.pop();

                            for (int d = 0; d < 4; d++) {
                                int nx = x + dx[d], ny = y + dy[d]; 
                                if (blocked[x][y][d] == true || !in(nx, ny)) {
                                    continue;
                                }
                                if (isInfected[nx][ny] == 0) {
                                    new_grids.emplace(nx * m + ny);
                                    continue;
                                }
                                if (visited[nx][ny] == 0 && isInfected[nx][ny] == 1) {
                                    visited[nx][ny] = 1;
                                    q.emplace(nx, ny);
                                }
                            }
                        }
                        if (new_grids.size() > max_impact) {
                            mx = i;
                            my = j;
                            max_impact = new_grids.size();
                        }
                    }
                }
            }

            if (success) {
                return wall_used;
            }
            // cout << mx << " " << my << endl;
            // add walls
            queue<pair<int, int>> q;
            q.emplace(mx, my);
            while (q.size()) {
                auto [x, y] = q.front();
                q.pop();
                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d], ny = y + dy[d]; 
                    if (!in(nx, ny)) {
                        continue;
                    }
                    if (blocked[x][y][d] == true) {
                        continue;
                    }
                    if (isInfected[nx][ny] == 0) {
                        blocked[x][y][d] = true;
                        wall_used++;
                        continue;
                    }
                    if (isInfected[nx][ny] == 1) {
                        q.emplace(nx, ny);
                        isInfected[nx][ny] = -1;
                    }
                }
            }

            // cout << "walls: " << wall_used << endl;
            // for (int i = 0 ; i < n; i++) {
            //     for (int j = 0; j < m; j++) {
            //         cout << isInfected[i][j] << " "; 
            //     }
            //     cout << endl;
            // }

            // expand
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    visited[i][j] = 0;
                }
            }
            set<pair<int, int>> next_step;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (isInfected[i][j] == 1 && !visited[i][j]) {
                        q = queue<pair<int, int>>();
                        q.emplace(i, j);
                        visited[i][j] = 1;
                        while (q.size()) {
                            auto [x, y] = q.front();
                            q.pop();
                            for (int d = 0; d < 4; d++) {
                                if (blocked[x][y][d]) {
                                    continue;
                                }
                                int nx = x + dx[d], ny = y + dy[d];
                                if (!in(nx, ny)) {
                                    continue;
                                }
                                if (isInfected[nx][ny] == 0) {
                                    next_step.emplace(nx, ny);
                                }
                                if (isInfected[nx][ny] == 1 && !visited[nx][ny]) {
                                    visited[nx][ny] = 1;
                                    q.emplace(nx, ny);
                                }
                            }
                        }
                    }
                }
            }
            for (auto [tx, ty] : next_step) {
                isInfected[tx][ty] = 1;
            }
            if (game_over()) {
                return wall_used;
            }
        }
        return -1;
    }
};

int main() {
    vector<vector<int>> isInfected = {{0,1,0,0,0,0,0,1},{0,1,0,0,0,0,0,1},{0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,0}};
    Solution s;
    cout << s.containVirus(isInfected);
}