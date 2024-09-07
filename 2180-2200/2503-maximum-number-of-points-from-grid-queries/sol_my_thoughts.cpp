#include <bits/stdc++.h>
using namespace std;

#include <ranges>

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
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
        int queriesN = queries.size();
        vector<int> sorted_id(queriesN);
        ranges::iota(sorted_id, 0);
        ranges::sort(sorted_id, [&](int x, int y) { return queries[x] < queries[y]; });

        int n = grid.size(), m = grid[0].size();

        auto in = [&](int x, int y) {
            return 0 <= x && x < n && 0 <= y && y < m;
        };
        const int dx[] = {0, 0, -1, 1};
        const int dy[] = {1, -1, 0, 0};

        unordered_set<pair<int, int>, TupleHash> failed;
        failed.emplace(0, 0);

        unordered_set<pair<int, int>, TupleHash> visited;
        queue<pair<int, int>> q;
        vector<int> ans(queriesN);
        int prev_cnt = 0;
        int last_qv = -1;
        for (int i = 0; i < queriesN; i++) {
            int qv = queries[sorted_id[i]];
            if (qv == last_qv) {
                ans[sorted_id[i]] = prev_cnt;
                continue;
            }
            last_qv = qv;
            
            unordered_set<pair<int, int>, TupleHash> to_erase;
            for (auto& [x, y] : failed) {
                if (grid[x][y] < qv) {
                    q.emplace(x, y);
                    prev_cnt++;
                    to_erase.emplace(x, y);
                    visited.emplace(x, y);
                }
            }
            for (auto& e : to_erase) {
                failed.erase(e);
            }
            while (q.size()) {
                auto [x, y] = q.front();
                q.pop();
                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d], ny = y + dy[d];
                    if (!in(nx, ny)) {
                        continue;
                    }
                    if (grid[nx][ny] >= qv) {
                        failed.emplace(nx, ny);
                    } else if (!visited.contains({nx, ny})) {
                        q.emplace(nx, ny);
                        prev_cnt++;
                        visited.emplace(nx, ny);
                    }
                }
            }
            ans[sorted_id[i]] = prev_cnt;
        }
        return ans;
    }
};