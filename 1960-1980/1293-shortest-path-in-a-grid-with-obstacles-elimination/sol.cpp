#include <bits/stdc++.h>
using namespace std;

template <class T>
size_t HashCombine(size_t seed, const T& value) {
    return seed ^ (std::hash<T>{}(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
}

struct TupleHash {
    size_t operator()(const auto& tuple) const {
        size_t res = 0;
        std::apply([&res](const auto&... args) { ((res = HashCombine(res, args)), ...); }, tuple);
        return res;
    }
};

class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        vector<int> dx = {0, 0, -1, 1};
        vector<int> dy = {-1, 1, 0, 0};
        int n = grid.size(), m = grid[0].size();
        if (m == 1 && n == 1) {
            return 0;
        }
        auto in = [&](int x, int y) {
            return 0 <= x && x < n && 0 <= y && y < m;
        };

        unordered_set<tuple<int, int, int>, TupleHash> visited_states; // x, y, used
        queue<tuple<int, int, int, int>> q; // x, y, used, dis 
        q.emplace(0, 0, 0, 0);
        visited_states.emplace(0, 0, 0);
        while (q.size()) {
            auto [x, y, used, dis] = q.front();
            q.pop();
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (!in(nx, ny)) continue;
                // cout << nx << " " << ny << endl;
                int new_used = grid[nx][ny] ? used + 1 : used;
                if (visited_states.contains({nx, ny, new_used})) {
                    continue;
                }
                if (nx == n - 1 && ny == m - 1 && new_used <= k) {
                    return dis + 1;
                }
                if (new_used > k) continue;
                q.emplace(nx, ny, new_used, dis + 1);
                visited_states.emplace(nx, ny, new_used);
            }
        }
        return -1;
    }
};

int main() {
    Solution s;
    vector<vector<int>> grid = {{0,0,0},{1,1,0},{0,0,0},{0,1,1},{0,0,0}};
    int k = 1;
    cout << s.shortestPath(grid, k);
}